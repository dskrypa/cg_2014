/**
	A BoardObject is an object that can be drawn on a Board using GLUT.
	The point that a BoardObject stores for its position is its bottom-left
	corner.
	@author Douglas Skrypa
	@version 2014.02.17
*/

#include "BoardObject.h"
#include <GLUT/glut.h>
#include <iostream>

/**
	Construct a default BoardObject at (0, 0) with no area.
*/
BoardObject::BoardObject()
{
	x = 0;
	y = 0;
	height = 0;
	width = 0;
}

/**
	Construct a custom BoardObject.
	@param x the x value of a point
	@param y the y value of a point
	@param w the width
	@param h the height
*/
BoardObject::BoardObject(double x, double y, double w, double h)
{
	this->x = x;
	this->y = y;
	height = h;
	width = w;
}

/**
	Returns the x value of this BoardObject's current position.
	@return the x value of this BoardObject's position point
*/
double BoardObject::getX()
{
	return x;
}

/**
	Returns the y value of this BoardObject's current position.
	@return the y value of this BoardObject's position point
*/
double BoardObject::getY()
{
	return y;
}

/**
	Determines whether or not this BoardObject contains a given point.
	@param cx the x value of a point to check
	@param cy the y value of a point to check
	@return true if the given point falls within the bounds of this BoardObject
*/
bool BoardObject::contains(double cx, double cy)
{
	bool r = (cx >= x);
	bool l = (cx <= (x + width));
	bool u = (cy >= y);
	bool d = (cy <= (y + height));

	return (r && l) && (u && d);
}

/**
	Draws the representation of this BoardObject using GLUT.
*/
void BoardObject::display()
{
	glBegin(GL_POLYGON);
		glColor3f(1.0, 1.0, 1.0);
		glVertex2f(0.0+x, 0.0+y);
		glVertex2f(0.0+x, height+y);
		glVertex2f(width+x, height+y);
		glVertex2f(width+x, 0.0+y);
	glEnd();
}

/**
	Determines whether or not this BoardObject would occupy part of the same
	space as the given board object if it were to advance one space in the given
	direction.
	@param bObj a BoardObject on the same Board as this one
	@param dir the direction that this BoardObject is traveling
	@return true if either of the vertices of the [movement direction] side
		would end up inside of the given BoardObject
*/
bool BoardObject::willCollideWith(BoardObject& bObj, int dir)
{
	double leftX = x, rightX = x + width;
	double bottomY = y, topY = y + height;

	switch(dir){
		case 1:		//check top of this, bottom of bObj
			return bObj.contains(leftX, topY+1) || bObj.contains(rightX, topY+1);
		case -1:	//check bottom of this, top of bObj
			return bObj.contains(leftX, bottomY-1) || bObj.contains(rightX, bottomY-1);
		case 2:		//check left of this, right of bObj
			return bObj.contains(leftX-1, topY) || bObj.contains(leftX-1, bottomY);
		case -2:	//check right of this, left of bObj
			return bObj.contains(rightX+1, topY) || bObj.contains(rightX+1, bottomY);
	}
	return false;
}
