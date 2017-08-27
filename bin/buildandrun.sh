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

function print_usage {
	echo "Usage: $0
	  -d, --debug     Compile with gcc -g for debug mode
	  -w, --windows   Cross compile in Linux for Windows  
	  -s, --sixty     Compile in 64 bit mode only for windows"
	exit 1;
}

for arg in "$@"; do
  shift
  case "$arg" in
    "--debug")    set -- "$@" "-d" ;;
    "--windows")  set -- "$@" "-w" ;;
    "--sixty")    set -- "$@" "-s" ;;
    *)            set -- "$@" "$arg"
  esac
done

cmake_flags=". ";

while getopts "dws" opt
do
  case "$opt" in
	"d") cmake_flags+="-Ddebug=ON" ;;
    "w") windows=true ;;
    "s") sixty=true ;;
    "?") print_usage;
  esac
done

if [ ! $windows ] && [ $sixty ]; then
	echo "Invalid option --sixty without --windows"
	exit 1
fi

if [ $windows ]; then
	if [ $sixty ]; then
		test x86_64-w64-mingw32-cmake -Dcrosscompile="ON" -Dsixty="ON" .
	else
		test i686-w64-mingw32-cmake -Dcrosscompile="ON" .
	fi
	test make
	test wine ./windows/NeuralNetwork.exe
else
	test cmake $cmake_flags
	test make
	test ./unix/neural_network
fi
