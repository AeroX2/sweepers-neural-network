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

test ../../cmake-windows/bin/cmake.exe -G "MSYS Makefiles"
test /c/MinGW/msys/1.0/bin/make.exe
test neural_network.exe
