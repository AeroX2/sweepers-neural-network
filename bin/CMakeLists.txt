cmake_minimum_required(VERSION 2.8.9)
project (neural_network)

set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O3 -Wall -Wextra")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g -Wall -Wextra -fsanitize=undefined")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/../cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR})

file(GLOB_RECURSE SOURCES ../src/*.cpp ../src/*.hpp)

add_executable(neural_network ${SOURCES})
target_link_libraries(neural_network ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARIES})
