/**
	A Terrarium Wall
	@author Douglas Skrypa
	@version 2014.04.09
*/

#include "TerrWall.h"
#include <iostream>

TerrWall::TerrWall(){}

/**
	Construct a TerrWall with the given specs.
*/
TerrWall::TerrWall(Position p, Dimensions d, unsigned char r, unsigned char g, unsigned char b){
	generateDisplayID();		//Obtain a display list ID
	setPos(p);					//Store initial position
	setDims(d);					//Store object size
	
	glNewList(getDisplayID(), GL_COMPILE);
		glColor3ub(r, g, b);
		glTranslatef(0.0f, 0.0f, dim.h/2.0f);
		glScalef(d.w, d.l, d.h);
		glutWireCube(1.0f);
	glEndList();
}
