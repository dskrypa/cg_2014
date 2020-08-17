Computer Graphics, Homework 2
Douglas Skrypa
2014.03.09

Files included:
Clickable.cpp  hw2Runner.cpp  Icon.h         LogicGate.h   Terminal.h  Wire.h
Clickable.h    Icon.cpp       LogicGate.cpp  Terminal.cpp  Wire.cpp

==============================
Compile & Run:

Working directory: DouglasSkrypa_CGHomework2/
Command to compile:

g++ -Wall -o test.x source/* -lglut -lGLU -lGL -lm

Command to run:

./test.x

==============================

Choose a LogicGate type by clicking one of the icons in the top-left corner.
Click anywhere to place the chosen gate at that location.  After a gate is
placed, to place another gate, a type must be selected again.

Terminals may be connected by clicking on one, then another.  The connection
type and color may be chosen via the right-click menu.  These settings persist
until changed.

The screen can be cleared through an option in the right-click menu, which also
includes an option to close the program.  It can also be closed by pressing
[ESC] or [Q].
