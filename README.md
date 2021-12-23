# Tetra
this is the classical game of tetris made in c++ and using the SDL framework

## project structure
### classes 
  * renderer: renders a window at 60 frames a second
  * renderee: base class for rendered objects 
  * rect:     base class for objects made of rectangles that will render
  * piece:    class that are the tetris pieces
  * board:    class in which the game is played in
  * placed:   class that renders all the filled cells of the board
  * vec2:     base template class for 2 class T objects (x, y)
  * complex:  template class that behaves like a complex number 
## 

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
  * create folder build
  * move to folder build in the console
  * use the command "cmake .."
  * use the command "make"

## Running the project:
  * use the command ./tetris