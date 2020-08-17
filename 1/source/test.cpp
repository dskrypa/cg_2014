/**
	Homework 1
	Test for the Board, BoardObject, and Character classes.
	@author Douglas Skrypa
	@version 2014.02.17
*/

#include "Board.h"
#include "BoardObject.h"
#include "Character.h"
#include <GLUT/glut.h>
#include <iostream>

using namespace std;

//Construct the Character and Board, placing the Character near the middle
int width = 600;
int height = 500;
Character p (width/2.0, height/2.0);
Board board (p, width, height);
int lastDir;			//Last direction for autorun
bool autorun = false;

//Function declarations
void display();
void idle();
void kbSpecial(int, int, int);
void kbNormal(unsigned char, int, int);
void reshape(int, int);

int main(int argc, char *argv[])
{
	//Construct obstacles to place on the board
	BoardObject bObj[7];
	bObj[0] = BoardObject(0, 0, width, 15);
	bObj[1] = BoardObject(0, height-15, width, 15);
	bObj[2] = BoardObject(0, 0, 15, height);
	bObj[3] = BoardObject(width-15, 0, 15, height);
	bObj[4] = BoardObject(100, 100, 200, 20);
	bObj[5] = BoardObject(500, 300, 50, 100);
	bObj[6] = BoardObject(400, 400, 20, 50);

	for(int x = 0; x < 7; x++){		//...then place them on the board
		board.addItem(bObj[x]);
	}

	//GLUT stuff
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Board");
	glutDisplayFunc(display);
	glutSpecialFunc(kbSpecial);
	glutKeyboardFunc(kbNormal);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}

/**
	Function for GLUT to call to display the board
*/
void display()
{
	//Call the board's display method
	board.display();
}

/**
	Function for GLUT to call when the window size/shape changes
*/
void reshape(int x, int y)
{
	width = x; height = y;
	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)width, 0.0, (GLdouble)height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutPostRedisplay();
}

/**
	Function for GLUT to call when the system is idle
*/
void idle()
{
	//glutPostRedisplay();
	/**
		glutPostRedisplay() is called when an action changes the state of the
		board or the items on it, so it does not need to be constantly called
		while idle

		If autorun is on, simulate a keypress for the most recent direction
		given by the user
	*/
	if(autorun){
		kbSpecial(lastDir, 0, 0);
	}
}

/**
	Function for GLUT to call when non-ASCII keys are pressed; defines actions
	to take based on the key pressed.
*/
void kbSpecial(int c, int x, int y)
{
	Character& player = board.getPlayer();

	switch(c){
		case GLUT_KEY_UP:
			board.attemptMove(player, 1);
			lastDir = GLUT_KEY_UP;
			break;
		case GLUT_KEY_DOWN:
			board.attemptMove(player, -1);
			lastDir = GLUT_KEY_DOWN;
			break;
		case GLUT_KEY_LEFT:
			board.attemptMove(player, 2);
			lastDir = GLUT_KEY_LEFT;
			break;
		case GLUT_KEY_RIGHT:
			board.attemptMove(player, -2);
			lastDir = GLUT_KEY_RIGHT;
			break;
	}
}

/**
	Function for GLUT to call when ASCII keys are pressed; defines actions
	to take based on the key pressed.
*/
void kbNormal(unsigned char key, int x, int y)
{
	Character& player = board.getPlayer();

	switch(key){
		case 27:case'q':case'Q':
			exit(0);
		case 'r':case 'R':
			autorun = !autorun;
			break;
		case '+':
			player.incSpeed();
			break;
		case '-':
			player.decSpeed();
			break;
	}
}
