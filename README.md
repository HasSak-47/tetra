# Tetra
this is the classical game of tetris made in c++ and using the SDL framework

the project is divided into several classes:
* complex: this class is used for the use of complex numbers to rotate the pieces
* renderer: this class renders the windows used for the project
* renderee: this class is an object that is rendered like a piece or the board
* interact: this class can read and respond to keyboard inputs
* board: this is a child of renderee so it could render
* piece: this is a child of renderee so it could render and a child of interact so it could be moved

## file structure
    src
        include
            board.h
            complex.h
            piece.h
            renderer.h
            unique_vector.h

        lib
            board.cpp
            main.cpp
            piece.cpp
            renderee.cpp
            renderer.cpp

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)


## Building the project:
    -create folder build
    -move to folder build in the console
    -use the command "cmake .."
    -use the command "make"

## Running the project:
    -use the command ./tetris

