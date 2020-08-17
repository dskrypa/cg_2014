/**
	Animal that exists inside a terrarium
	@author Douglas Skrypa
	@version 2014.04.09
*/

#include "Animal.h"
#include <iostream>

Animal::Animal(){}

/**
	Construct a generic Animal with the given dimensions at the given position
	@param p position
	@param d dimensions
*/
Animal::Animal(Position p, Dimensions d){
	generateDisplayID();		//Obtain a display list ID
	setPos(p);					//Store initial position
	setDims(d);					//Store object size
}

/**
	Obtain this Animal's movement speed
	@return float movement speed
*/
float Animal::getMovementSpeed(){
	return movementSpeed;
}

/**
	Update position and facing direction
	@param theta angle in which to turn
	@param dx distance to travel along the x axis
	@param dy distance to travel along the y axis
*/
void Animal::updatePosition(float theta, float dx, float dy){
	glPushMatrix();
	
	glTranslatef(dx, dy, 0.0f);
	//glRotatef(theta, 0.0f, 0.0f, 1.0f);
	//glTranslatef(-pos.x, -pos.y, -pos.z);
	glCallList(getDisplayID());
	
	glPopMatrix();
	
	pos.x += dx;
	pos.y += dy;
}

/**
	Determine whether moving in the current direction is possible, and changes
	direction if needbe.
	@param xBoundLow min legal x position
	@param xBoundHigh max legal x position
	@param yBoundLow min legal y position
	@param yBoundHigh max legal y position
*/
void Animal::attemptMove(float xBoundLow, float xBoundHigh, float yBoundLow, float yBoundHigh){
	float newX = pos.x + xDir * 3;
	float newY = pos.y + yDir * 3;
	
	if(((newX <= xBoundLow) && (xDir == -1)) || ((newX >= xBoundHigh) && (xDir == 1))){
		xDir *= -1;
	}
	if(((newY <= yBoundLow) && (yDir == -1)) || ((newY >= yBoundHigh) && (yDir == 1))){
		yDir *= -1;
	}
	updatePosition(0, xDir, yDir);
}

