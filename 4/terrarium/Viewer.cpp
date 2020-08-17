/**
	Launcher / viewer for the terrarium
	@author Douglas Skrypa
	@version 2014.05.09
*/

//Common libraries
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <string>
//GLUT is in a different place on mac vs linux/pc
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
//Project headers
#include "Env3D.h"
#include "Camera.h"
#include "Terrarium.h"
//not recognized as defined by MS Visual Studio Pro 2013
#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE 0x809D
#endif

//Additional mouse "buttons" undefined by GLUT
#define MOUSE_SCROLL_UP		3
#define MOUSE_SCROLL_DOWN	4

//Current state information
Env3D env;
int windowWidth = 700, windowHeight = 700;
int windowID, menuID;
bool rotate = false;						//Mouse actions occurring
int rotateX = -1, rotateY = -1;				//Last X/Y coord for mouse
unsigned int frameDelay = 40;				//Delay between frames in ms
Camera cam;									//The camera - controls POV
Terrarium terr;								//Terrarium (main feature)
Dimensions tdim = {50, 20, 30};				//Dimensions for the terrarium / environment

//Function prototypes
void init();
void display();
void reshape(int, int);
void timer(int);
void kbNormal(unsigned char, int, int);
void kbSpecial(int, int, int);
void mouse(int, int, int, int);
void mouseMove(int, int);
void mainMenu(int);
void shutdown();

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(200, 40);
	windowID = glutCreateWindow("3D Viewer");

	//Menus
	menuID = glutCreateMenu(mainMenu);
		glutAddMenuEntry("Reset Position", 1);
		glutAddMenuEntry("Reset Focus", 2);
		glutAddMenuEntry("Exit", 0);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);

	//Register GLUT callbacks
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMove);
	glutKeyboardFunc(kbNormal);
	glutSpecialFunc(kbSpecial);
	glutReshapeFunc(reshape);
	glutTimerFunc(frameDelay, timer, 0);

	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);

	init();

	glutMainLoop();
	return 0;
}

void shutdown(){
	glutDestroyMenu(menuID);
	glutDestroyWindow(windowID);
	exit(0);
}

void init(){
	float terrX = tdim.w / 2.0f;
	float terrY = tdim.l / 2.0f;
	Position min = {-terrX, -terrY, 0, 0};
	Position max = {terrX, terrY, (float)tdim.h, 0};

	//			fps	winWidth	winHeight	min point	max point
	env = Env3D(30, windowWidth, windowHeight, min, max);

	//			Target			Up		radius	angXY	angZW
	cam = Camera({0, 0, 0, 0}, {0, 0, 1, 0}, 52, 179.1, 44.4);
	cam.spin(0, 0);

	terr = Terrarium(&env);
	terr.populate();
}

/**
	Draw all objects
*/
void display(){
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	cam.refresh();
	
	terr.display();
	
	glFlush();
	glutSwapBuffers();
}

/**
	Main menu
*/
void mainMenu(int choice){
	switch(choice){
		case 0:
			shutdown();
			break;
		case 1:
			cam.setRadius(18);
			cam.setAngles(0, 0);
			cam.spin(0, 0);
			break;
		case 2:
			cam.changeTarget(0, 0, 0);
			cam.spin(0, 0);
			break;
		default:
			break;
	}
}

/**
	Function for GLUT to call to advance the animation
*/
void timer(int id){
	glutPostRedisplay();
	glutTimerFunc(frameDelay, timer, 0);
}

/**
	Function for GLUT to call when ASCII keys are pressed; defines actions
	to take based on the key pressed.
*/
void kbNormal(unsigned char key, int x, int y){
	switch(key){
		case 27:case 'q':case 'Q':
			shutdown();
			break;
		case '6':
		case 'X':	cam.moveCam(1.0f, 0.0f, 0.0f);	break;
		case '4':
		case 'x':	cam.moveCam(-1.0f, 0.0f, 0.0f);	break;
		case '8':
		case 'Y':	cam.moveCam(0.0f, 1.0f, 0.0f);	break;
		case '2':
		case 'y':	cam.moveCam(0.0f, -1.0f, 0.0f);	break;
		case 'Z':	cam.moveCam(0.0f, 0.0f, 1.0f);	break;
		case 'z':	cam.moveCam(0.0f, 0.0f, -1.0f);	break;
		default:	break;
	}
}

/**
	Function for GLUT to call when non-ASCII keys are pressed; defines actions
	to take based on the key pressed.
*/
void kbSpecial(int c, int x, int y){
	Position pos;
	switch(c){
		case GLUT_KEY_F1:
			pos = cam.getTarget();
			std::cout<<"Focus: ("<<pos.x<<", "<<pos.y<<", "<<pos.z<<")\n";
			break;
		case GLUT_KEY_F2:
			pos = cam.getPosition();
			std::cout<<"Camera: ("<<pos.x<<", "<<pos.y<<", "<<pos.z<<", "<<pos.w<<")\n";
			break;
		case GLUT_KEY_F3:
			pos = cam.getUp();
			std::cout<<"Up: ("<<pos.x<<", "<<pos.y<<", "<<pos.z<<")\n";
			break;
		case GLUT_KEY_F4:
			std::cout<<"Camera radius: "<<cam.getRadius()<<", angle XY: "<<cam.getAngleXY()<<" rad, angle ZW: "<<cam.getAngleZW()<<" rad\n";
			break;
		default:	break;
	}
}

/**
	Handle mouse input
*/
void mouse(int button, int state, int x, int y){
	if(state == GLUT_DOWN){
		switch(button){
			case MOUSE_SCROLL_UP:		cam.zoomIn(1);		break;
			case MOUSE_SCROLL_DOWN:		cam.zoomOut(1);		break;
			case GLUT_RIGHT_BUTTON:		rotate = true;		break;
			default:					break;
		}
	} else if(state == GLUT_UP){
		switch(button){
			case GLUT_RIGHT_BUTTON:
				rotate = false;
				rotateX = -1;
				rotateY = -1;
				break;
			default:
				break;
		}
	}
}

/**
	Handle camera spinning while clicking & dragging mouse
*/
void mouseMove(int x, int y){
	if(rotate){
		if(rotateX != -1){
			float rx = x - rotateX;
			if(rx != 0){
				cam.spinXY(-rx);
			}
		}
		if(rotateY != -1){
			float ry = y - rotateY;
			if(ry != 0){
				cam.spinZW(ry);
			}
		}
	}
	rotateX = x;
	rotateY = y;
}

/**
	Handle window reshaping
*/
void reshape(int w, int h){
	windowWidth = w; windowHeight = h;
	h = (h == 0 ? 1 : h);
	float ratio = w * 1.0f / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	//fov angle in yz plane, window aspect ratio, near clip, far clip
	gluPerspective(45.0f, ratio, 0.1f, 300.0f);
	glMatrixMode(GL_MODELVIEW);
	cam.spin(0, 0);
	glutPostRedisplay();
}