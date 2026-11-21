$prev_working_directory = $PWD

try {
	Set-Location $PSScriptRoot

	Write-Host "Rebuilding project"

	& '../../scripts/make-all.ps1' -target lophus -builds msvc-*

	if ($LASTEXITCODE -ne 0) {
		exit 1
	}

	Write-Host "Creating AST for consistency check"

	& '../../build/win32-msvc-dbg/Debug/lophus.exe' -config check-ast.toml

	if ($LASTEXITCODE -ne 0) {
		exit 1
	}

	Write-Host "Diffing ASTs"

	$diff = Compare-Object (Get-Content parse.cpp.lophus.expected-ast) (Get-Content parse.cpp.lophus.current-ast)

	if ($diff -ne $null) {
		Write-Host "AST consistency check failed: There are differences in the generated AST" -ForegroundColor Red

		$diff

		exit 1
	} else {
		Write-Host "Success"
	}

	Write-Host "Running benchmark"

	& '../../build/win32-msvc-rel/Release/lophus.exe' -config bench.toml
} finally {
	Set-Location $prev_working_directory
}
