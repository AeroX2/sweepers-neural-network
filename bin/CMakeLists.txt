cmake_minimum_required(VERSION 2.8.9)
project (neural_network)

option(debug "debug" OFF)
if (WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
	set(CMAKE_CXX_COMPILER /usr/bin/clang++)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra")
endif()

if (debug)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fsanitize=undefined")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/../cmake")

#set(SDL2_INCLUDE_DIR "H:\\.Desktop\\SDL2\\x86_64-w64-mingw32\\include")
#set(SDL2_PATH "H:\\.Desktop\\SDL2\\x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR})

file(GLOB_RECURSE SOURCES ../src/*.cpp ../src/*.hpp)

add_executable(neural_network ${SOURCES})
target_link_libraries(neural_network ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARIES})
