# Tetra
this is the classical game of tetris made in c++ and using the SDL2 framework

### what is expected
when the game begins in the console and prints:
  * starting game...
  * total scores loaded: 1
  * setting rendered objects...
  * starting threads...

after that all of this may appear in any particular order
  * loop thread: ####
  * seed: ####
  * renderer thread: ####
  * act thread: ####

this will appear when the window is closed
  * setting value
  * closing rendered window
  * ended falling loop
  * I had no idea how to put this so it prints this :p
  * ended threads
  * ended program (hopefully) without issues!

how to use
* controls of the game: left key, right key and down key
* the window can be closed at any time to end the program
* afer losing the game you have to close the window
* the program continues after you close the window and will ask for input in the console

## rubric points
### Loops, Functions, I/O
#### The project demonstrates an understanding of C++ functions and control structures
one example of a control structure used in the project
  * switch: line 82 at piece.cpp
  * while: line 117 at piece.cpp
  * do while: line 30 at piece.cpp
  * if else: line 55
  * if: line 121 at piece.cpp
  * range based for: line 144 at piece.cpp
  * for: line 160 at piece.cpp

#### The project reads data from a file and process the data, or the program writes data to a file.
the constructor of `piece` line 37 at board_piece.cpp loads the data of the piece into the program, and the usage of the constructor is at line 13 at board_piece.cpp

#### The project accepts user input and processes the input.
the program ask for the users name and then compares it to a data base to make sure it isn't repeated and prints the score of the user

### Object Oriented Programming
#### The project uses Object Oriented Programming techniques.
  * `vec2`: base template class for 2 class T objects (x, y)
    * definition in src/include/complex.h line 7
  * `complex`: template class that behaves like a complex number 
    * definition in src/include/complex.h line 43 
    * child of vec2
  * `renderer`: renders a window at 60 frames a second
    * declaration in src/include/renderer.h line 22
    * definition in src/include/renderer.h line 32
  * `renderee`: base class for rendered objects
    * declaration in src/include/renderer.h line 24
    * definition in src/include/renderer.h line 81
  * `interact`: base class for a class that can be controlled with the keyboard
    * declaration in src/include/renderer.h line 26
    * definition in src/include/renderer.h line 108
  * `rect`: base class for objects made of rectangles that will render
    * definition in src/include/rect.h line 6
    * child of renderee
  * `piece`: class that are the tetris pieces
    * definition in src/include/piece.h line 6
    * child of renderee and interact
  * `board`: class in which the game is played in
    * definition in src/include/board.h line 7
    * child of class rect
  * `placed`: class that renders all the filled cells of the board
    * declared in board.h line 27
#### Classes use appropriate access specifiers for class members.
definitions of the classes
  * `vec2<T>` in src/include/complex.h line 7 
  * `complex<T>` in src/include/complex.h line 43 
  * `renderer` in src/include/renderer.h line 32
  * `renderee` in src/include/renderer.h line 81
  * `interact` in src/include/renderer.h line 108
  * `rect` in src/include/rect.h line 6
  * `piece` in src/include/piece.h line 6
  * `board` in src/include/board.h line 7
  * `placed` in src/include/board.h line 27
#### Class constructors utilize member initialization lists.
  * `vec2<T>`
    * src/include/complex.h line 14
    * src/include/complex.h line 15
    * src/include/complex.h line 16
    * src/include/complex.h line 17
  * `complex<T>`
    * src/include/complex.h line 50
    * src/include/complex.h line 51
    * src/include/complex.h line 53
    * src/include/complex.h line 54
    * src/include/complex.h line 56
    * src/include/complex.h line 57
  * `renderer`
    * src/lib/renderer.cpp line 8
    * src/lib/renderer.cpp line 10
  * `renderee`
    * src/lib/renderee.cpp line 5
    * src/lib/renderee.cpp line 10
  * `rect`
    * src/lib/rect.cpp line 3
    * src/lib/rect.cpp line 7
  * `board`
    * src/lib/board.cpp line 20
  * `placed`
    * src/lib/board.cpp line 25
  * `piece`
    * src/lib/board_piece.cpp line 37
    * src/lib/piece.cpp line 175
    * src/lib/piece.cpp line 183
### Classes abstract implementation details from their interfaces.
lines of declaration of class methods
* `board`
  * void set_rectangles() line 31 at board.cpp
  * board::tile& operator[](vec2i) line 59 at board.cpp
  * bool evaluate next(piece&) line 63 at board_piece.cpp
* `piece`
  * void rotate() line 126 at board_piece.cpp
  * void move_down() line 169 at board_piece.cpp
  * void move_side(side s) line 190 at board_piece.cpp
  * void set_padding() line 203 at board_piece.cpp
  * void act() line 69 at piece.cpp
  * void loop() line 108 at piece.cpp
  * void set_rectangles() line 138 at piece.cpp
  * void operator(const piece& other) line 157 at piece.cpp
* `rect`
  * void set_rectangles() line 35 at rect.cpp
  * vec2i get_padding() line 37 at rect.cpp
* `renderee`
  * void render() line 24 at renderee.cpp
  * void set_pos(float, float) line 35 at renderee.cpp
  * void set_rectangles() line 39 at renderee.cpp
* `renderer`
  * void render() line 22 at renderer.cpp
  * bool should_close() line 88 at renderer.cpp
  * SDL_Event get_event() line 92 at renderer.cpp
  * vec2i get_dimentions() line 97 at renderer.cpp
  * vec2i get_unit_dimentions() line 101 at renderer.cpp
  * vec2i get_unit() line 106 at renderer.cpp
  * SDL_Renderer* get_renderer() line 110 at renderer.cpp
  * void wait_for_render() line 115 at renderer.cpp
### Classes encapsulate behavior
### Classes follow an appropriate inheritance hierarchy.
### Overloaded functions allow the same function to operate on different parameters.
### Derived class functions override virtual base class functions.
all childs from renderee override the function set_rectangles:
  * `piece` line 8 at file piece.h
  * `board` line 10 at file board.h
  * `placed` line 29 at file board.h

### Templates generalize functions in the project.
  * operator+ overloading outside class members of vec2 line 38 at complex.h


## Memory Management
### The project makes use of references in function declarations.
### The project uses destructors appropriately.
### The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.
### The project follows the Rule of 5.
vec2 and complex uses follows the rule of 5
* line 11 -> 17 and 47 -> 57 in complex.gh
### The project uses move semantics to move data, instead of copying it, where possible.
### The project uses smart pointers instead of raw pointers.
the only instance of the new operator in the project is in creating pointers to structs that will be assigned to a unique_ptr

## Concurrency
### The project uses multithreading.
  line 67 -> 71 creates threads and lines 72 -> 74 joins the threads
### A promise and future is used in the project.
  the class renderer has the promise and future that it is used to get if the window closed with the variables ended and promise_end
### A mutex or lock is used in the project.
  mutex is used in line 78 at file piece.cpp
### A condition variable is used in the project.
  line 130 at file piece.cpp

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