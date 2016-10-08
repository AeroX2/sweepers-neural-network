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

test cmake -Ddebug="$debug" .
test make
test ./neural_network
