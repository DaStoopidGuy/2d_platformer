# 2D Platformer
![main menu screenshot](menu.png)  

![in game screenshot](game.png)
Welcome to my 2D Platformer project  
**This project is currently under development...**  
I used the raylib game library to develop it in C.  

My goal with this particular project is the learn the basics of game architecture along with how things work in C language and working with makefiles and/or cmake.

## Quickstart
This project uses CMake as its build system.  
To build and run the project,  
navigate to the root directory of the project and run the following commands in your terminal/shell:  

```shell
$ mkdir build
$ cd build
$ cmake ..
$ make run
```  

I have also created a Makefile for using just `make` as the build system:

```shell
$ make -B
```

To generate `compile_commands.json` file for clangd, run the following:  

```shell
$ bear -- make -B
```

Support for OSes other than linux is currently untested. Cmake automatically fetches the library for you.
 And the library is included for linux usage with make.
