#!/bin/sh

function test {
    "$@"
    local status=$?
    if [ $status -ne 0 ]; then
        echo "error with $1" >&2
		exit
    fi
    return $status
}

if [ "$1" == "sixty" ]; then
	test ../../cmake-windows/bin/cmake.exe -G "MSYS Makefiles" -Dwindows="ON" -Dsixty"ON"
else
	test ../../cmake-windows/bin/cmake.exe -G "MSYS Makefiles" -Dwindows="ON"
fi
test /c/MinGW/msys/1.0/bin/make.exe
test NeuralNetwork.exe
