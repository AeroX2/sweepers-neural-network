# sweepers-neural-network
Neural Network created in C++. Based heavily off <http://ai-junkie.com> (Smart Sweepers)  

# Building and running under Linux
```
$ install sdl2_devel, sdl2_image_devel, sdl2_ttf_devel
$ cd sweepers-neural-network/bin  
For 64-bit, You will have to pass sixty to ./buildandrun.sh
$ ./buildandrun.sh sixty    
For 32-bit       
$ ./buildandrun.sh
```
# Building and running under Windows
```
$ install MinGW
$ download sdl2_devel_mingw, sdl2_image_devel_mingw, sdl2_ttf_devel_mingw
$ extract sdl2_devel_mingw, sdl2_image_devel_mingw, sdl2_ttf_devel_mingw to libs
$ open the MSYS shell ({MINGW}\msys\1.0\msys.bat)
$ cd sweepers-neural-network/bin  
For 64-bit, You will have to pass sixty to ./buildandrun-msys.sh and install MinGW-w64
$ ./buildandrun-msys.sh sixty    
For 32-bit       
$ ./buildandrun-msys.sh
```
# Manual build
```
$ cd bin  
$ cmake .  
$ make  
```
