# sweepers-neural-network
Neural Network created in C++. Based heavily off <http://ai-junkie.com> (Smart Sweepers)  

# Building and running under Linux
```
$ install sdl2_devel, sdl2_image_devel, sdl2_ttf_devel
$ cd sweepers-neural-network/bin  
For 64-bit, You will have to pass --sixty to ./buildandrun.sh
$ ./buildandrun.sh (-s|--sixty)
For 32-bit       
$ ./buildandrun.sh
```
# Building and running under Windows
```
$ install MinGW with MSys
$ install CMake
$ extract the SDL2-2.0.5.zip in the libs folder
$ open the MSYS shell ({MINGW}\msys\1.0\msys.bat)
$ cd sweepers-neural-network/bin
For 64-bit, You will have to pass --sixty to ./buildandrun-msys.sh and install MinGW-w64
$ ./buildandrun-msys.sh (-s|--sixty)    
For 32-bit       
$ ./buildandrun-msys.sh
```
# Manual build
```
$ cd bin  
$ cmake .  
$ make  
```
