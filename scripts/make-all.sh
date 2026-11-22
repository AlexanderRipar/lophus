#!/usr/bin/env bash

if [[ $# -eq 0 ]]; then
	echo "Usage: $0 targets..." >&2
	exit 1
fi

targets=$*

cxx_compilers=(g++ g++ clang++ clang++)
c_compilers=(gcc gcc clang clang)
build_types=(debug release debug release)

outputs=()

pids=()

# Start compilations asynchronously.
for i in {0..3}; do
	output=$(mktemp -t lophus-build.XXXXXX)
	outputs[$i]=$output

	cxx_compiler=${cxx_compilers[$i]}
	c_compiler=${c_compilers[$i]}
	build_type=${build_types[$i]}

	if [[ $build_type == "release" ]]; then
		short_build_type="rel"
		monobuild="ON"
	else
		short_build_type="dbg"
		monobuild="OFF"
	fi

	build_name="linux-$c_compiler-$short_build_type"

	( cd "$(dirname ${BASH_SOURCE[0]})/.." && cmake -S . -B build/$build_name -DCMAKE_CXX_COMPILER=$cxx_compiler -DCMAKE_C_COMPILER=$c_compiler -DCMAKE_BUILD_TYPE=$build_type -DMONOBUILD=$monobuild && cmake --build build/$build_name --target $targets 2>&1 ) > $output &

	pids[$i]=$!
done

failed_compiles=()

# Wait for each compilation to complete.
for i in {0..3}; do
	wait ${pids[$i]}

	status=$?

	c_compiler=${c_compilers[$i]}
	build_type=${build_types[$i]}

	if [[ $build_type == "release" ]]; then
		short_build_type="rel"
	else
		short_build_type="dbg"
	fi

	build_name="linux-$c_compiler-$short_build_type"

	if [[ $status -ne 0 ]]; then
		failed_compiles+=($build_name)
	fi

	output=${outputs[$i]}

	echo ""
	echo "################# $build_name #################"
	echo ""
	echo ""

	# Clean up and print output.
	# This is all on one line because the shell apparently can't deal with
	# windows crlf line endings, and those are inevitably going to sneak in
	# here.
	grep -E -v -e "^\[ *[0-9]+%\] (Building CXX object|Linking CXX executable|Building ASM object|Building C object|Linking C shared library) " -e "^-- Configuring done " -e "^-- Generating done " -e "^-- Build files have been written to: " -e "^g?make(\[[0-9]+\])?: \*\*\* " $output | sed -r -e "s/^\[ *[0-9]+%\] //"

	rm $output
done

failed_compile_count=${#failed_compiles[@]}

echo ""

if [[ ${#failed_compiles[@]} -ne 0 ]]; then
	echo "The following builds failed:"

	for failed_compile in "${failed_compiles[@]}"; do
		echo "    - $failed_compile"
	done

	exit 1
else
	echo "All builds succeeded"

	exit 0
fi
