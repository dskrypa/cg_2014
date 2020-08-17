#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <string>
#include "Camera.h"
#include "Terrarium.h"
#include "Env3D.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

//Additional mouse "buttons" undefined by GLUT
#define MOUSE_SCROLL_UP		3
#define MOUSE_SCROLL_DOWN	4

//Current state information
Env3D env;
int windowWidth = 700, windowHeight = 700;
int windowID, menuID;
int lastX = -1, lastY = -1;					//Stored X/Y for camera movement
bool moveXY = false, moveZW = false;		//True to allow camera movement
unsigned int frameDelay = 100;				//Delay between frames in millisec
Camera cam;									//The camera - controls POV
Terrarium terr;
Bug b;
Dimensions tdim = {50, 20, 30};
int terrWidth = 50;		//x
int terrDepth = 20;		//y
int terrHeight = 30;	//z

int axesList;

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
void buildAxisLines();			//TESTING PURPOSES ONLY

int main(int argc, char **argv){
	glutInit(&argc, argv);						//Pass pointers to runtime args
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(1400, 40);
	windowID = glutCreateWindow("3D Viewer");

	//Menus
	menuID = glutCreateMenu(mainMenu);
		glutAddMenuEntry("Reset Position", 1);
		glutAddMenuEntry("Reset Focus", 2);
		glutAddMenuEntry("Exit", 3);
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

	float terrX = tdim.w/2.0f;
	float terrY = tdim.l/2.0f;
	Position min = {-terrX, -terrY, 0, 0};
	Position max = {terrX, terrY, (float)terrHeight, 0};
					//fps	winWidth	winHeight		min point	max point
	env = Env3D(30, windowWidth, windowHeight, min, max);
	//float t[] = {-8, 1, 6}, u[] = {0, 0, 1};
	Position t = {0, 0, 0, 0}, u = {0, 0, 1, 0};
	//cam = Camera(t, u, 60, -3.16f, 0.78f);				//Target, Up, radius, ang, ang
	cam = Camera(t, u, 12, 180, 45);				//Target, Up, radius, ang, ang
	cam.spin(0, 0);
	
	Position p = {0, 0, 0, 0};
	b = Bug(&env, p);
	
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
	buildAxisLines();
	terr = Terrarium(&env);
	//terr.populate();
}

/**
	Draw all objects
*/
void display(){
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	cam.refresh();
	
	glPushMatrix();
	glCallList(axesList);
	glPopMatrix();
	
	glPushMatrix();
	b.display();
	glPopMatrix();
	
	terr.display();
	
	glFlush();
	glutSwapBuffers();
}

/**
	Main menu
*/
void mainMenu(int choice){
	switch(choice){
		case 1:
			cam.setRadius(3);
			cam.setAngles(0, 0);
			cam.spin(0, 0);
			break;
		case 2:
			cam.changeTarget(0, 0, 0);
			cam.spin(0, 0);
			break;
		case 3:
			shutdown();
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
		case 27:case'q':case'Q':
			shutdown();
		case 'X':	cam.shiftTarget(1.0f, 0.0f, 0.0f);	break;
		case 'x':	cam.shiftTarget(-1.0f, 0.0f, 0.0f);	break;
		case 'Y':	cam.shiftTarget(0.0f, 1.0f, 0.0f);	break;
		case 'y':	cam.shiftTarget(0.0f, -1.0f, 0.0f);	break;
		case 'Z':	cam.shiftTarget(0.0f, 0.0f, 1.0f);	break;
		case 'z':	cam.shiftTarget(0.0f, 0.0f, -1.0f);	break;
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
		case GLUT_KEY_UP:		b.advance(1);	break;
		case GLUT_KEY_DOWN:		b.advance(-1);	break;
		case GLUT_KEY_LEFT:		b.rotate(-1);	break;
		case GLUT_KEY_RIGHT:	b.rotate(1);	break;
		default:				break;
	}
}

/**
	Handle mouse input
*/
void mouse(int button, int state, int x, int y){
	if(state == GLUT_DOWN){
		switch(button){
			case MOUSE_SCROLL_UP:		cam.zoomIn(1);	break;
			case MOUSE_SCROLL_DOWN:		cam.zoomOut(1);	break;
			case GLUT_LEFT_BUTTON:		moveXY = true;	break;
			case GLUT_RIGHT_BUTTON:		moveZW = true;	break;
			default:					break;
		}
	} else if(state == GLUT_UP){
		switch(button){
			case GLUT_LEFT_BUTTON:		moveXY = false;	lastY = -1;	break;
			case GLUT_RIGHT_BUTTON:		moveZW = false;	lastX = -1;	break;
			default:					break;
		}
	}
}

/**
	Handle camera spinning while clicking & dragging mouse
*/
void mouseMove(int x, int y){
	if(moveXY && (lastX != -1)){
		float mdx = x - lastX;
		if(mdx == 0){return;}
		cam.spinXY(-mdx);
	}
	if(moveZW && (lastY != -1)){
		float mdy = y - lastY;
		if(mdy == 0){return;}
		cam.spinZW(mdy);
	}
	lastX = x;
	lastY = y;
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

/**	Axis lines for reference	*/
void buildAxisLines(){
	axesList = glGenLists(1);
	glNewList(axesList, GL_COMPILE);
		//X axis (red)
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_LINES);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(100.0f, 0.0f, 0.0f);
		glEnd();
	
		//Y axis (blue)
		glColor3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_LINES);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 100.0f, 0.0f);
		glEnd();
	
		//Z axis (green)
		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_LINES);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 100.0f);
		glEnd();
	
		//W axis [line y = x] (purple)
		glColor3f(1.0f, 0.0f, 1.0f);
		glBegin(GL_LINES);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(100.0f, 100.0f, 0.0f);
		glEnd();
	
		//Z = W (white)
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINES);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(100.0f, 100.0f, 100.0f);
		glEnd();	
	glEndList();
}
