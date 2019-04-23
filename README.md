# Game engine #

[![Build Status](https://travis-ci.org/Game-technology-group-2/project-teleport.svg?branch=master)](https://travis-ci.org/Game-technology-group-2/project-teleport)

A game written in C++, using OpenGL and SDL2, glm and Glew.

## Licenses ##
This project is licensed under the GNU GPLv3 License.

The music file `bensound-instinct.ogg` is sourced from `www.bensound.com`.

## Dependencies ##
* SDL2
* SDL2_image
* SFML (only for the audio)
* OpenGL
* Glew
* GLM (included as a submodule)

## Build ##
### GNU/Linux ###
```
mkdir build
cd build
cmake ..
cmake --build .
```

### Windows ###
To build this project on Windows, it is required to : 

- Download and compile the latest source code of the dependencies (previously enumerated).

- Place the `.lib` files in their respective directories. Going from the root of this repository,
  this would be `..\libraries\Release\x64\` for a 64 bits release build (and their equivalent for `Debug` and/or `Win32`).

- Place the `.dll` files in the build directory, next to the `.exe` file generated.


A copy of the game built (32 bits, release build) can be downloaded here :
[Framadrop hosting](https://framadrop.org/r/W0-zXnKd5B#P4wXsmzXw+3j2eiHTCoNKHWeCs3gkNHxij9gi8xpSkU=)
[WeTransfer hosting](https://we.tl/t-UQRNuAWQZw)
