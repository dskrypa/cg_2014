/**
	A terrarium in which animals can exist
	@author Douglas Skrypa
	@version 2014.04.09
*/
#include <iostream>
#include "Terrarium.h"

Terrarium::Terrarium(){}

/**
	Construct a Terrarium with a specific width, height, and depth.
	@param width the width of the Terrarium
	@param height the height of the Terrarium
	@param depth the depth of the Terrarium
*/
Terrarium::Terrarium(Env3D* environment){	//x, y, z
	//std::cout<<"Terrarium(): Constructing... h="<<height<<" w="<<width<<" d="<<depth<<std::endl;
	
	env = environment;
	Position min = env->getMinPoint();
	Position max = env->getMaxPoint();
	Dimensions d = {env->getBoundedWidth(), env->getBoundedLength(), env->getBoundedHeight()};
	
	//TerrWall wall = TerrWall(p, d, 255, 255, 255);
	//entities.push_back(wall);
	
	int floorID = glGenLists(1);
	//int wallsID = glGenLists(1);
	glNewList(floorID, GL_COMPILE);
		glColor3ub(200, 200, 0);
		glBegin(GL_QUADS);
			glVertex3f(min.x, min.y, 0.0f);
			glVertex3f(min.x, max.y, 0.0f);
			glVertex3f(max.x, max.y, 0.0f);
			glVertex3f(max.x, min.y, 0.0f);
		glEnd();
		glColor3ub(255, 255, 255);
		glTranslatef(0.0f, 0.0f, d.h/2.0f);
		glScalef(d.w, d.l, d.h);
		glutWireCube(1.0f);
	glEndList();
	
	/*glNewList(wallsID, GL_COMPILE);
		glColor3ub(r, g, b);
		glTranslatef(0.0f, 0.0f, dim.h/2.0f);
		glScalef(d.w, d.l, d.h);
		glutWireCube(1.0f);
	glEndList();*/
	
	
	TerrEntity floor = TerrEntity(floorID);
	floor.setPos(min);
	floor.setDims(d);
	entities.push_back(floor);
}

/**
	Populates this Terrarium with TerrEntities.
*/
void Terrarium::populate(){
	Position p1 = {2.0f, 3.0f, 1.05f};
	Bug b1 = Bug(env, p1);
	Position p2 = {5.0f, 8.0f, 1.05f};
	Bug b2 = Bug(env, p2);
	Position p3 = {-2.0f, 8.0f, 1.05f};
	Penguin a3 = Penguin(p3);
	
	animals.push_back(b1);
	animals.push_back(b2);
	animals.push_back(a3);
	
	for(int x = 0; (unsigned)x < animals.size(); x++){
		animals[x].updatePosition(90.0f, 0, 0);
	}
}

/**
	Draw the walls and contents of this Terrarium
*/
void Terrarium::display(){
	for(int x = 0; (unsigned)x < animals.size(); x++){
		animals[x].attemptMove(xBoundLow, xBoundHigh, yBoundLow, yBoundHigh);
	}
	
	for(int x = 0; (unsigned)x < entities.size(); x++){
		glPushMatrix();
		glCallList(entities[x].getDisplayID());
		glPopMatrix();
		//std::cout<<entities[x].getDisplayId()<<std::endl;
	}
}

/**
	Obtain a pointer to the vector containing the entities in this Terrarium
	@return std::vector<TerrEntity>* containing the entities in this Terrarium
*/
std::vector<TerrEntity>* Terrarium::getEntities(){
	return &entities;
}
