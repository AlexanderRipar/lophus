#!/usr/bin/env bash

if [[ $# -ne 1 || ($1 != 'gcc' && $1 != 'clang') ]]; then
	echo "Usage: ${BASH_SOURCE[0]} (gcc|clang)" 1>&2
	exit 1
fi

echo 'Rebuilding project'

(cd "$(dirname ${BASH_SOURCE[0]})/../.." && 'scripts/make-all.sh' lophus)

if [[ $? -ne 0 ]]; then
	exit 1
fi

echo 'Creating AST for consistency check'

(cd $(dirname ${BASH_SOURCE[0]}) && "../../build/linux-$1-dbg/lophus" -config check-ast.toml)

echo 'Diffing ASTs'

ast_diff=$(cd $(dirname ${BASH_SOURCE[0]}) && diff parse.cpp.lophus.expected-ast parse.cpp.lophus.current-ast)

if [[ $ast_diff ]]; then
	printf 'AST consistency check failed: There are differences in the generated AST\n%s\n' "${ast_diff}"
	exit 1
else
	echo 'Success'
fi

echo 'Running benchmark'

(cd $(dirname ${BASH_SOURCE[0]}) && "../../build/linux-$1-rel/lophus" -config bench.toml)
