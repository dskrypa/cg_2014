/**
	A Penguin.
	@author Douglas Skrypa
	@version 2014.04.09
*/

#include "Penguin.h"

Penguin::Penguin(Position p){
	generateDisplayID();		//Obtain a display list ID
	setPos(p);					//Store initial position
	Dimensions d = {0.8f, 0.8f, 1.0f};
	setDims(d);
	moveSpeedSecs = 0.8f;
	spinSpeedSecs = M_PI * 0.125f;
	initDisplay();
}

/**
	Build the display lists for this Penguin
*/
void Penguin::initDisplay(){
	int beakID = glGenLists(1);
	glNewList(beakID, GL_COMPILE);
		glColor3ub(255, 155, 0);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glutSolidCone(0.1f, 0.3f, 16, 16);
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glEndList();
	
	
	glNewList(getDisplayID(), GL_COMPILE);
		glColor3ub(0, 0, 0);
		
		//Body
		glTranslatef(pos.x, pos.y, pos.z);
		glScalef(dim.w, dim.l, dim.h);
		glutSolidSphere(1.0f, 20, 20);
		
		//Head
		glTranslatef(0.0f, 0.0f, 0.9f);
		glutSolidSphere(0.5f, 16, 16);
		
		//Beak
		glTranslatef(0.0f, -0.45f, 0.0f);
		glCallList(beakID);
	glEndList();
}
