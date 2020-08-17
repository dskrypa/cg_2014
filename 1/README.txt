Computer Graphics, Homework 1
Douglas Skrypa
2014.02.17

Files included:
test.cpp
Board.h
Board.cpp
BoardObject.h
BoardObject.cpp
Character.h
Character.cpp

==============================
Compile & Run:

Working directory: DouglasSkrypa_CGHomework1/source/
Command to compile:

g++ -Wall -o test.x Board.cpp Board.h BoardObject.cpp BoardObject.h Character.cpp Character.h test.cpp -lglut -lGLU -lGL -lm

Command to run:

./test.x

------------------------------
Alternate:

in file ~/bin/compileGL:

#!/bin/bash
g++ -Wall -o "$@" -lglut -lGLU -lGL -lm
#EOF


Working directory: DouglasSkrypa_CGHomework1/
Compile & run:

rm test.x; compileGL test.x source/*; ./test.x

------------------------------
I am still very new to C/C++; I will try to include a makefile for the next
assignment.

==============================

Move the character by pressing the arrow keys.  If you press [R], the character
will continue to run in the last direction that you pressed, until it runs into
an obstacle, you change its direction, or you press [R] again to toggle autorun
off.  The movement speed for both manual and autorun movement can be adjusted by
pressing [+] and [-].  The character's color changes based on its current speed.
The minimum speed is 0 (no movement), and the maximum is set to 12.

Program commands:
[ESC]		Quit
[Q]			Quit
[R]			Toggle autorun (default: off)
[+]			Increase character's speed
[-]			Decrease character's speed
[UP]		Move character up
[DOWN]		Move character down
[LEFT]		Move character left
[RIGHT]		MOve character right


