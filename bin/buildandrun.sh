#!/bin/sh

function test {
	echo $@
    "$@"
    local status=$?
    if [ $status -ne 0 ]; then
        echo "error with $1" >&2
	exit
    fi
    return $status
}

if [ "$1" == "debug" ]; then
	debug="ON"
else
	debug="OFF"
fi

if [ "$1" == "windows" ]; then
	if [ "$2" == "sixty" ]; then
		test x86_64-w64-mingw32-cmake -Dcrosscompile="ON" -Dsixty="ON" .
	else
		test i686-w64-mingw32-cmake -Dcrosscompile="ON" .
	fi
	test make
	test wine NeuralNetwork.exe
else
	test cmake -Ddebug="$debug" .
	test make
	test ./neural_network
fi
