cmake_minimum_required(VERSION 3.21)
project (neural_network)

option(web "web" OFF)
option(sixty "sixty" OFF)
option(debug "debug" OFF)
option(windows "windows" OFF)
option(crosscompile "crosscompile" OFF)

if (windows)
	message("Building for Windows")
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/windows)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
elseif (crosscompile)
	message("Cross compiling for Windows")
	if (sixty)
		set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
	else()
		set(CMAKE_CXX_COMPILER i686-w64-mingw32-g++)
	endif()
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/windows)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
	set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "-static-libgcc -static-libstdc++ -static")
elseif (web)
	message("Building for web")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/web)
else()
	message("Building for Linux")
	set(CMAKE_CXX_COMPILER clang++)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/unix)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra")
endif()

if (crosscompile OR windows)
	if (sixty)
		set(SDL2_PATH              "${PROJECT_SOURCE_DIR}/../libs/SDL2-2.0.5/x86_64-w64-mingw32")
		file(GLOB SDL_DLLS         "${PROJECT_SOURCE_DIR}/../libs/SDL2-2.0.5/x86_64-w64-mingw32/bin/*.dll")
		file(COPY ${SDL_DLLS} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
	else()
		set(SDL2_PATH              "${PROJECT_SOURCE_DIR}/../libs/SDL2-2.0.5/i686-w64-mingw32")
		file(GLOB SDL_DLLS         "${PROJECT_SOURCE_DIR}/../libs/SDL2-2.0.5/i686-w64-mingw32/bin/*.dll")
		file(COPY ${SDL_DLLS} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
	endif()
endif()

if (debug)
	message("Building with debug flag")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

file(GLOB_RECURSE SOURCES ../src/*.cpp ../src/*.hpp)
file(GLOB_RECURSE DATA ${CMAKE_CURRENT_SOURCE_DIR}/data/*)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/../cmake")

if (web)
	add_executable(neural_network ${SOURCES})
	target_include_directories(${PROJECT_NAME} PUBLIC "../libs/SDL2-2.30.0/include")
	target_include_directories(${PROJECT_NAME} PUBLIC "../libs/SDL2_image-2.8.2/include")
	target_include_directories(${PROJECT_NAME} PUBLIC "../libs/SDL2_ttf-2.22.0")

	target_link_options(${PROJECT_NAME} PRIVATE
		-sMODULARIZE=1
		"-sEXPORT_NAME='Main'"
		-sINVOKE_RUN=0
		-sDISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=0
		"-sEXPORTED_FUNCTIONS=['_main']"
		"-sEXPORTED_RUNTIME_METHODS=['callMain', 'ccall', 'cwrap']"
		-sSDL2_IMAGE_FORMATS=PNG
		-sFORCE_FILESYSTEM=1
		-sUSE_SDL=2
		-sUSE_SDL_TTF=2
		-sUSE_SDL_IMAGE=2
		-sUSE_LIBPNG
		-sUSE_FREETYPE=1
		-O3
		--preload-file data/
	)
	add_custom_command(
		TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy
			${CMAKE_SOURCE_DIR}/index.html
			web/index.html
	)
else()
	find_package(SDL2 REQUIRED)
	find_package(SDL2_ttf REQUIRED)
	find_package(SDL2_image REQUIRED)
	include_directories(${SDL2_INCLUDE_DIR} 
				${SDL2_TTF_INCLUDE_DIR}
				${SDL2_IMAGE_INCLUDE_DIR})
						
	set(LINKER_FLAGS 	${SDL2_MAIN} 
				${SDL2_LIBRARY}
				${SDL2_TTF_LIBRARY}
				${SDL2_IMAGE_LIBRARY})

	if (windows)
		add_executable(NeuralNetwork ${SOURCES})
		target_link_libraries(NeuralNetwork -lmingw32 ${LINKER_FLAGS})
	elseif (crosscompile)
		add_executable(NeuralNetwork.exe ${SOURCES})
		target_link_libraries(NeuralNetwork.exe -lmingw32 ${LINKER_FLAGS})
	else()
		add_executable(neural_network ${SOURCES})
		target_link_libraries(neural_network ${LINKER_FLAGS})
	endif()
endif()
