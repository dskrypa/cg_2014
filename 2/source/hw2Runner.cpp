/**
	Homework 2
	@author Douglas Skrypa
	@version 2014.03.09
*/

#include <GLUT/glut.h>
#include <vector>
#include "Clickable.h"
#include "Icon.h"
#include "Terminal.h"
#include "LogicGate.h"
#include "Wire.h"
#include <iostream>

//States
#define DRAW_TERMINAL		1
#define DRAW_GATE_AND		2
#define DRAW_GATE_OR		3
#define DRAW_GATE_NOT		4
#define DRAW_WIRE_START		5
#define DRAW_WIRE_END		6

//Current state information
int windowWidth = 700, windowHeight = 700;
int currentState = -1;
int mostRecentId = 0;

//Stored items
Icon icons[3];
std::vector<LogicGate> gates;
std::vector<Wire> wires;

//Variables for creating a new Wire
int wireShape = LAYOUT_XY;
LogicGate DEFAULT = LogicGate(NOT_GATE, -1, -1, -999);
LogicGate* gateA = &DEFAULT;
LogicGate* gateB = &DEFAULT;
int termA = -1, termB = -1;
int r=1, g=1, b=1;
float splitPoint=0.5;

//Function declarations
void init();
void display();
void reshape(int, int);
void kbNormal(unsigned char, int, int);
void mouse(int, int, int, int);
bool checkGates(int, int);
void setActive(int);
void registerWireEndpoint(LogicGate*, const int);
void placeWire();
void colorMenu(int);
void shapeMenu(int);
void mainMenu(int);
void wireMenu(int);

int main(int argc, char *argv[])
{
	//Required by GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Logic Gates");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, (GLdouble)windowWidth, 0, (GLdouble)windowHeight);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Initialize icons & menus
	init();

	int cMenu = glutCreateMenu(colorMenu);
		glutAddMenuEntry("Red",1);
		glutAddMenuEntry("Green",2);
		glutAddMenuEntry("Blue",3);
		glutAddMenuEntry("Cyan",4);
		glutAddMenuEntry("Magenta",5);
		glutAddMenuEntry("Yellow",6);
		glutAddMenuEntry("White",7);
		glutAddMenuEntry("Black",8);
	int wMenu = glutCreateMenu(wireMenu);
		glutAddMenuEntry("1/4",1);
		glutAddMenuEntry("1/3",2);
		glutAddMenuEntry("1/2",3);
		glutAddMenuEntry("2/3",4);
		glutAddMenuEntry("3/4",5);
	int sMenu = glutCreateMenu(shapeMenu);
		glutAddMenuEntry("XY", 1);
		glutAddMenuEntry("YX", 2);
		glutAddMenuEntry("XYX", 3);
		glutAddMenuEntry("YXY", 4);
		glutAddSubMenu("Split point", wMenu);
	glutCreateMenu(mainMenu);
		glutAddSubMenu("Wire Shape", sMenu);
		glutAddSubMenu("Wire Color", cMenu);
		glutAddMenuEntry("Clear", 1);
		glutAddMenuEntry("Exit", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	//Register GLUT callbacks
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(kbNormal);
	glutReshapeFunc(reshape);
	glutMainLoop();

	return 0;
}

/**
	Initialize storage variables and icons
*/
void init()
{
	gates.clear();
	wires.clear();
	mostRecentId = 0;
	icons[0] = Icon("  AND  ", 0, windowHeight-20, 99, 20, ++mostRecentId);
	icons[1] = Icon("  OR  ", 100, windowHeight-20, 99, 20, ++mostRecentId);
	icons[2] = Icon("  NOT  ", 200, windowHeight-20, 99, 20, ++mostRecentId);
}

/**
	Draw all objects
*/
void display()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	for(int id = 1; id <= mostRecentId; id++){
		glPushMatrix();
		glCallList(id);
		glPopMatrix();
	}

	glFlush();
	glutSwapBuffers();
}

/**
	Handle window reshaping
*/
void reshape(int x, int y)
{
	windowWidth = x; windowHeight = y;
	glViewport(0,0,windowWidth,windowHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, (GLdouble)windowWidth, 0, (GLdouble)windowHeight);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutPostRedisplay();
}

/**
	Set the color of new Wires based on the given menu choice
*/
void colorMenu(int choice)
{
	switch(choice){
		case 1:		r = 1; g = 0; b = 0;	break;	//Red
		case 2:		r = 0; g = 1; b = 0;	break;	//Green
		case 3:		r = 0; g = 0; b = 1;	break;	//Blue
		case 4:		r = 0; g = 1; b = 1;	break;	//Cyan
		case 5:		r = 1; g = 0; b = 1;	break;	//Magenta
		case 6:		r = 1; g = 1; b = 0;	break;	//Yellow
		case 7:		r = 1; g = 1; b = 1;	break;	//White
		case 8:		r = 0; g = 0; b = 0;	break;	//Black
	}
}

/**
	Set the shape of new Wires based on the given menu choice
*/
void shapeMenu(int choice)
{
	switch(choice){
		case 1:
			wireShape = LAYOUT_XY;
			break;
		case 2:
			wireShape = LAYOUT_YX;
			break;
		case 3:
			wireShape = LAYOUT_XYX;
			break;
		case 4:
			wireShape = LAYOUT_YXY;
			break;
	}
}

/**
	Clear the screen or close the program based on the given meny choice
*/
void mainMenu(int choice)
{
	switch(choice){
		case 1:
			init();
			display();
			break;
		case 2:
			exit(0);
	}
}

/**
	Set the split point for new Wires based on the given menu choice
*/
void wireMenu(int choice)
{
	switch(choice){
		case 1:	splitPoint = 1/4.0;	break;
		case 2:	splitPoint = 1/3.0;	break;
		case 3:	splitPoint = 1/2.0;	break;
		case 4:	splitPoint = 2/3.0;	break;
		case 5:	splitPoint = 3/4.0;	break;
	}
}

/**
	Function for GLUT to call when ASCII keys are pressed; defines actions
	to take based on the key pressed.
*/
void kbNormal(unsigned char key, int x, int y)
{
	switch(key){
		case 27:case'q':case'Q':
			exit(0);
	}
}

/**
	Handle mouse input

	NOTE: Due to not having a middle button on my laptop, the middle-click is
	untested, but its functions are working with left-clicks.
*/
void mouse(int button, int state, int x, int y)
{
	y = windowHeight-y;		//The value that is passed in for y is inverted

	bool leftClick = (button == GLUT_LEFT_BUTTON) && state == GLUT_DOWN;
	bool midClick = (button == GLUT_MIDDLE_BUTTON) && state == GLUT_DOWN;

	if(leftClick){
		if(icons[0].wasClicked(x, y)){
			currentState = DRAW_GATE_AND;
			setActive(0);
		} else if(icons[1].wasClicked(x, y)){
			currentState = DRAW_GATE_OR;
			setActive(1);
		} else if(icons[2].wasClicked(x, y)){
			currentState = DRAW_GATE_NOT;
			setActive(2);
		} else if(checkGates(x, y)){
		} else {
			switch(currentState){
				case DRAW_GATE_AND:
					icons[0].deactivate();
					gates.push_back(LogicGate(AND_GATE, x, y, ++mostRecentId));
					display();
					currentState = -1;
					break;
				case DRAW_GATE_OR:
					icons[1].deactivate();
					gates.push_back(LogicGate(OR_GATE, x, y, ++mostRecentId));
					display();
					currentState = -1;
					break;
				case DRAW_GATE_NOT:
					icons[2].deactivate();
					gates.push_back(LogicGate(NOT_GATE, x, y, ++mostRecentId));
					display();
					currentState = -1;
					break;
				case DRAW_WIRE_END:
					gateA->get(termA)->deactivate();
					gateA = &DEFAULT;
					termA = -1;
					display();
					currentState = -1;
					break;
			}
		}
	} else if(midClick){
		if(checkGates(x, y)){
		} else {
			switch(currentState){
				case DRAW_WIRE_END:
					gateA->get(termA)->deactivate();
					gateA = &DEFAULT;
					termA = -1;
					display();
					currentState = -1;
					break;
			}
		}
	}
}

/**
	Registers a potential end point for a Wire.
*/
void registerWireEndpoint(LogicGate* gate, const int term)
{
	Terminal* clickTarget = gate->get(term);
	if(!clickTarget->isActivated() || clickTarget->getType() == TERM_OUTPUT){
		if(gateA->equals(&DEFAULT)){
			gateA = gate;
			termA = term;
			gateA->get(termA)->activate();
			currentState = DRAW_WIRE_END;
		} else {
			bool notSameAsA = !gateA->equals(gate);
			bool notSameTerminalType = gateA->get(termA)->getType() != gate->get(term)->getType();
			if(notSameAsA && notSameTerminalType){
				gateB = gate;
				termB = term;
				gateB->get(termB)->activate();
				placeWire();
			} else {
				gateA->get(termA)->deactivate();
				gateA = &DEFAULT;
				termA = -1;
			}
			currentState = -1;
		}
	}
	display();
}

/**
	Creates a Wire with the given info, then resets the gate and terminal that
	has focus.
*/
void placeWire()
{
	int startX	= gateA->get(termA)->getX()+7;
	int startY	= gateA->get(termA)->getY()+7;
	int endX	= gateB->get(termB)->getX()+7;
	int endY	= gateB->get(termB)->getY()+7;

	wires.push_back(Wire(++mostRecentId, wireShape, startX, startY, endX, endY, r, g, b, splitPoint));

	gateA = &DEFAULT;
	gateB = &DEFAULT;
	termA = -1;
	termB = -1;
}

/**
	Sets the currently active icon, which indicates the type of gate that will
	be created
*/
void setActive(int type)
{
	for(int c = 0; c < 3; c++){
		if(c == type){
			icons[c].activate();
		} else {
			icons[c].deactivate();
		}
	}
	display();
}

/**
	Checks the mouse click position against all terminals registered to stored
	gates.
*/
bool checkGates(int x, int y)
{
	for(int i = 0; (unsigned)i < gates.size(); i++){
		int terms = 2;
		if(gates[i].multipleInputs()){
			terms += 1;
		}

		for(int n = 0; n < terms; n++){
			if(gates[i].get(n)->wasClicked(x, y)){
				registerWireEndpoint(&gates[i], n);
				return true;
			}
		}
	}
	return false;
}
