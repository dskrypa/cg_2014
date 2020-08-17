/**
	A Bug.
	@author Douglas Skrypa
	@version 2014.04.09
*/

#include "Bug.h"
#include <math.h>

Bug::Bug(){}

Bug::Bug(Env3D* environment, Position p){
	generateDisplayID();		//Obtain a display list ID
	env = environment;
	setPos(p);					//Store initial position
	Dimensions d = {0.8f, 1.0f, 0.8f};
	setDims(d);
	forward = 0;
	moveSpeedSecs = 0.25f;
	spinSpeedSecs = M_PI * 0.125f;
	initDisplay();
}

/**
	Build the display lists for this Bug
*/
void Bug::initDisplay(){
	int legID = glGenLists(1);
	glNewList(legID, GL_COMPILE);
		glColor3ub(126, 88, 38);
		glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
		glutSolidCone(0.1f, 0.7f, 16, 16);
		glRotatef(-180.0f, 0.0f, 1.0f, 0.0f);
	glEndList();
	
	
	glNewList(getDisplayID(), GL_COMPILE);
		glColor3ub(198, 106, 19);
		
		//glRotatef(90, 0, 0, 1);
		
		//Body
		//glTranslatef(pos.x, pos.y, pos.z);
		glScalef(dim.w, dim.l, dim.h);
		glutSolidSphere(1.0f, 20, 20);
		
		//Head
		glTranslatef(0.0f, 0.9f, 0.0f);
		glutSolidSphere(0.5f, 16, 16);
		
		//Legs
		glTranslatef(0.4f, -0.35f, -0.7f);
		glCallList(legID);
		glTranslatef(0.0f, -1.0f, 0.0f);
		glCallList(legID);
		glTranslatef(-0.7f, 1.0f, 0.0f);
		glCallList(legID);
		glTranslatef(0.0f, -1.0f, 0.0f);
		glCallList(legID);
	glEndList();
}
