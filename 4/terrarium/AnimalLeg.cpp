#include <cmath>
#include "AnimalLeg.h"


AnimalLeg::AnimalLeg(){}

AnimalLeg::AnimalLeg(Position p){
	generateDisplayID();
	initEntity(p, {0, 0, 0}, 0, 0, 0, 0);
	state = STILL;
	swingAngle = 26;
	swingDirection = 0;
	initDisplay();
}

void AnimalLeg::initDisplay(){
	glNewList(getDisplayID(), GL_COMPILE);
		glColor3ub(126, 88, 38);
		glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
		glutSolidCone(0.1f, 0.7f, 16, 16);
		glRotatef(-180.0f, 0.0f, 1.0f, 0.0f);
	glEndList();
}

void AnimalLeg::display(){
	glTranslatef(pos.x, pos.y, pos.z);
	glRotatef(swingAngle * state, 0, 0, 1);			//Rotate to simulate movement
	glCallList(getDisplayID());
	//glRotatef(-swingAngle * state, 0, 0, 1);		//Rotate back for next leg

	switch(state){
		case STILL:
			if(swingDirection < 0){
				state = BACK;
			} else if(swingDirection > 0) {
				state = EXTENDED;
			} else {
				swingDirection = pow(-1, rand() % 4);
			}
			break;
		case EXTENDED:
			state = STILL;
			swingDirection = -1;
			break;
		case BACK:
			state = STILL;
			swingDirection = 1;
			break;
		default:	break;
	}
}

/*	Self-explanatory get methods	*/	
LegState AnimalLeg::getLegState(){	return state;}
