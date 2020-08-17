/**
	Animal that exists inside a terrarium
	@author Douglas Skrypa
	@version 2014.04.09
*/

#include "Animal.h"
#include <math.h>
#include <iostream>

Animal::Animal(){}

/**
	Obtain the distance that this Animal should travel in one frame
	@return float movement speed
*/
float Animal::getMoveSpeedPerFrame(){
	return moveSpeedSecs / env->getTargetFps();
}

float Animal::getSpinSpeedPerFrame(){
	return spinSpeedSecs / env->getTargetFps();
}

/**
	Rotate this Animal by the given amount
	@param theta an angle in radians
*/
void Animal::rotate(int steps){
	forward += spinSpeedSecs * -steps;
}

/**
	Advance in current direction at the current movement speed
	@param steps the number of steps to advance
*/
void Animal::advance(int steps){
	float xp = cos(forward);
	float yp = sin(forward);
	float d = moveSpeedSecs * steps;
	
	float nx = pos.x + xp * d;
	float ny = pos.y + yp * d;
	Position np = {nx + 1, ny + 1, pos.z};
	
	if(env->isInBounds(np)){
		pos.x = nx;
		pos.y = ny;
	}
}

/**
	Perform transformations and call display list to display this Animal
*/
void Animal::display(){
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	glRotatef(Env3D::radToDeg(forward) - 90, 0, 0, 1);
	glCallList(getDisplayID());
	glPopMatrix();
}

/**
	Update position and facing direction
	@param theta angle in which to turn
	@param dx distance to travel along the x axis
	@param dy distance to travel along the y axis
*/
void Animal::updatePosition(float theta, float dx, float dy){
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
}

