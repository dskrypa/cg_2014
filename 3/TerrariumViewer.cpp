/**
	Homework 3 - Terrarium
	@author Douglas Skrypa
	@version 2014.04.09
*/

#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <string>
#include "Terrarium.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

//Current state information
int windowWidth = 700, windowHeight = 700;
float cx = 25.0f, cy = 0.0f, cz = 55.0f;	//Camera position
float tx = 0.0f, ty = 0.0f, tz = 0.0f;		//Target position
float ux = 0.0f, uy = 0.0f, uz = 1.0f;		//Up position
float dx = 0.0f, dy = 0.0f, dz = 0.0f;		//Amount to change X/Y/Z pos
int lastX = -1, lastY = -1;					//Stored X/Y for camera movement
bool moveX = false, moveY = false, moveZ = false;
unsigned int frameDelay = 100;				//Delay between frames in millisec
int terrWidth = 50;		//x
int terrDepth = 20;		//y
int terrHeight = 30;	//z
Terrarium terr;

//Function declarations
void init();
void display();
void reshape(int, int);
void timer(int);
void kbNormal(unsigned char, int, int);
void kbSpecial(int, int, int);
void mouse(int, int, int, int);
void mouseMove(int, int);
void moveCamera(float, float, float);
void drawAxisLines();
void camSpinX(float);
void camSpinY(float);
void camSpinZ(float);

int main(int argc, char **argv){
	glutInit(&argc, argv);						//Pass pointers to runtime args
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Terrarium");

	//Register GLUT callbacks
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMove);
	glutKeyboardFunc(kbNormal);
	glutSpecialFunc(kbSpecial);
	glutReshapeFunc(reshape);
	glutTimerFunc(frameDelay, timer, 0);

	init();										//Initialize Terrarium
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}

/**
	Init
*/
void init(){
	terr = Terrarium(terrWidth, terrDepth, terrHeight);
	terr.populate();
}

/**
	Draw all objects
*/
void display(){
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(cx, cy, cz, tx + dx, ty + dy, tz + dz, ux, uy, uz);
	
	//drawAxisLines();
	terr.display();
	
	glFlush();
	glutSwapBuffers();
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
			exit(0);
		case 'X':	moveCamera(1.0f, 0.0f, 0.0f);	break;
		case 'x':	moveCamera(-1.0f, 0.0f, 0.0f);	break;
		case 'Y':	moveCamera(0.0f, 1.0f, 0.0f);	break;
		case 'y':	moveCamera(0.0f, -1.0f, 0.0f);	break;
		case 'Z':	moveCamera(0.0f, 0.0f, 1.0f);	break;
		case 'z':	moveCamera(0.0f, 0.0f, -1.0f);	break;
		default:	break;
	}
}

/**
	Function for GLUT to call when non-ASCII keys are pressed; defines actions
	to take based on the key pressed.
*/
void kbSpecial(int c, int x, int y){
	switch(c){
		default:	break;
	}
}

/**
	Handle mouse input
*/
void mouse(int button, int state, int x, int y){
	if(state == GLUT_DOWN){
		switch(button){
			case GLUT_LEFT_BUTTON:		moveY = true;	break;
			case GLUT_MIDDLE_BUTTON:	moveZ = true;	break;
			case GLUT_RIGHT_BUTTON:		moveX = true;	break;
			default:					break;
		}
	} else if(state == GLUT_UP){
		switch(button){
			case GLUT_LEFT_BUTTON:		moveY = false;	lastY = -1;	break;
			case GLUT_MIDDLE_BUTTON:	moveZ = false;	lastY = -1;	break;
			case GLUT_RIGHT_BUTTON:		moveX = false;	lastX = -1;	break;
			default:					break;
		}
	}
}

/**
	Handle camera spinning while clicking & dragging mouse
*/
void mouseMove(int x, int y){
	float mSpeed = 0.01f;
	
	if(moveX && (lastX != -1)){
		float mdx = x - lastX;
		if(mdx == 0){return;}
		mSpeed *= mdx / abs(mdx);		//Normalize to -1, 0, or 1
		camSpinX(mSpeed);
	}
	if(moveY && (lastY != -1)){
		float mdy = y - lastY;
		if(mdy == 0){return;}
		mSpeed *= mdy / abs(mdy);		//Normalize to -1, 0, or 1
		camSpinY(mSpeed);
	}
	if(moveZ && (lastY != -1)){
		float mdz = y - lastY;			//There is no Z axis to follow on mouse
		if(mdz == 0){return;}
		mSpeed *= mdz / abs(mdz);		//Normalize to -1, 0, or 1
		camSpinZ(mSpeed);
	}

	lastX = x;
	lastY = y;
}

/**	Spin camera	*/
void camSpinX(float speed){
	float rx = tx - cx;
	float ry = ty - cy;
	cx += (float)(cx + cos(speed) * rx - sin(speed) * ry);
	cy += (float)(cy + sin(speed) * rx + cos(speed) * ry);
}
void camSpinY(float speed){
	float ry = ty - cy;
	float rz = tz - cz;
	cz += (float)(cz + cos(speed) * rz - sin(speed) * ry);
	cy += (float)(cy + sin(speed) * rz + cos(speed) * ry);
}
void camSpinZ(float speed){
	float rx = tx - cx;
	float rz = tz - cz;
	cz += (float)(cz + cos(speed) * rz - sin(speed) * rx);
	cx += (float)(cx + sin(speed) * rz + cos(speed) * rx);
}

void moveCamera(float x, float y, float z){
	//std::cout<<"Moving camera by x: "<<x<<", y: "<<y<<", z: "<<z<<std::endl;
	cx += x;
	cy += y;
	cz += z;
	dx += x;
	dy += y;
	dz += z;
}

/**	Axis lines for reference	*/
void drawAxisLines(){
	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(100.0f, 0.0f, 0.0f);
	glEnd();
	
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 100.0f, 0.0f);
	glEnd();
	
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 100.0f);
	glEnd();
	glPopMatrix();
}
