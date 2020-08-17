/**
	A Bug.
	@author Douglas Skrypa
	@version 2014.05.09
*/

#include "Bug.h"

Bug::Bug(){}

Bug::Bug(Env3D* environment, Position p){
	initEntity(p, {0.8f, 1.0f, 0.8f}, 1.4f, -1.4f, -0.8f, 0.8f);
	initAnimal(environment, 0, 0.25f, PI * 0.125f);
	initAI(8, 18);
	initDisplay();
}

/**
	Build the display lists for this Bug
*/
void Bug::initDisplay(){
	AnimalLeg a = AnimalLeg({0.4f, -0.35f, -0.7f});
	AnimalLeg b = AnimalLeg({0.0f, -1.0f, 0.0f});
	AnimalLeg c = AnimalLeg({-0.7f, 1.0f, 0.0f});
	AnimalLeg d = AnimalLeg({0.0f, -1.0f, 0.0f});
	legs.push_back(a);
	legs.push_back(b);
	legs.push_back(c);
	legs.push_back(d);

	glNewList(getDisplayID(), GL_COMPILE);
		glColor3ub(198, 106, 19);

		//Body
		glScalef(dim.w, dim.l, dim.h);
		glutSolidSphere(1.0f, 20, 20);

		//Head
		glTranslatef(0.0f, 0.9f, 0.0f);
		glutSolidSphere(0.5f, 16, 16);

		for(unsigned x = 0; x < legs.size(); x++){
			legs[x].display();
		}
	glEndList();
}