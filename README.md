# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

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

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## Extensions
- Add possibility to store max user score into a file using the User cass and user namespace

## Project rubric
### README
- [X] A README with instructions is included with the project
- [X] The README indicates the new features you added to the game
- [X] The README includes information about each rubric point addressed

### Compiling and Testing

### Loops, Functions, I/O
- [X] The project reads data from a file and process the data, or the program writes data to a file.
Though the user class and namespace I keep and update the maximum reached score for every user.
- [X] The project accepts user input and processes the input.
Also through the User class and user namespace process input for user identification 
- [X] The project uses data structures and immutable variables.
Project uses vectors (vector of lines of input files) and uses constant variables in the argument of user namespace functions
- [X] The project demonstrates an understanding of C++ functions and control structures.
There are several loops and control flow and functions to abstract high commands and make code clearner

### Object Oriented Programming
 - [X] One or more classes are added to the project with appropriate access specifiers for class members.
Class user was added
 - [X] Class constructors utilize member initialization lists.
 User class uses initialization list on the constructor. 

### Memory Management
- [X] The project makes use of references in function declarations.
Majority of the functions added uses references 
- [X] The project uses move semantics to move data instead of copying it, where possible.
I used move semantics to move user object from main to last user namespace function as we won't need this object again in main

## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
