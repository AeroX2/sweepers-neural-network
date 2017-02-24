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
$ install MinGW with MSys
$ install CMake
$ download SDL2-devel-2.0.*-mingw.tar.gz       (https://www.libsdl.org/download-2.0.php),
           SDL2_image-devel-2.0.*-mingw.tar.gz (https://www.libsdl.org/projects/SDL_image), 
           SDL2_ttf-devel-2.0.*-mingw.tar.gz   (https://www.libsdl.org/projects/SDL_ttf)
$ extract SDL2-devel to libs
$ rename SDL2-2.0.* to SDL2-2.0.4
$ extract SDL2_image/x86_64-w64-mingw32 and SDL2_image/i686-w64-mingw32 to the SDL2-2.0.4 folder
$ extract SDL2_ttf/x86_64-w64-mingw32 and SDL2_ttf/i686-w64-mingw32 to the SDL2-2.0.4 folder
$ copy every *.dll file from SDL2-2.0.4\i686-w64-mingw32\bin to sweepers-neural-network\bin
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
