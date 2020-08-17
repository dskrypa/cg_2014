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
Terrarium::Terrarium(float width, float depth, float height){	//x, y, z
	//std::cout<<"Terrarium(): Constructing... h="<<height<<" w="<<width<<" d="<<depth<<std::endl;
	
	float x = width/2.0f;
	float y = depth/2.0f;
	
	xBoundLow = -x;
	xBoundHigh = x;
	yBoundLow = -y;
	yBoundHigh = y;
	
	Position p = {-x, -y, 0.0f};
	Dimensions d = {width, depth, height};
	
	TerrWall wall = TerrWall(p, d, 255, 255, 255);
	entities.push_back(wall);
	
	int floorID = glGenLists(1);
	glNewList(floorID, GL_COMPILE);
		glColor3ub(200, 200, 0);
		glBegin(GL_QUADS);
			glVertex3f(-x, -y, 0.0f);
			glVertex3f(-x, y, 0.0f);
			glVertex3f(x, y, 0.0f);
			glVertex3f(x, -y, 0.0f);
		glEnd();
	glEndList();
	TerrEntity floor = TerrEntity(floorID);
	floor.setPos(-x, -y, 0.0f);
	floor.setDims(width, depth, height);
	entities.push_back(floor);
}

/**
	Populates this Terrarium with TerrEntities.
*/
void Terrarium::populate(){
	Position p1 = {2.0f, 3.0f, 1.05f};
	Bug b1 = Bug(p1);
	Position p2 = {5.0f, 8.0f, 1.05f};
	Bug b2 = Bug(p2);
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
