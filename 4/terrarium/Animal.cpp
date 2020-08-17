/**
	Animal that exists inside a terrarium
	@author Douglas Skrypa
	@version 2014.05.09
*/

#include <math.h>
#include <iostream>
#include "Animal.h"

Animal::Animal(){}

/**
	Initialize common variables
*/
void Animal::initAnimal(Env3D* envr, float faceAng, float moves, float spins){
	generateDisplayID();		//Obtain a display list ID
	env = envr;
	forward = faceAng;
	moveSpeedSecs = moves;
	spinSpeedSecs = spins;
}

/**
	Initialize common AI variables
*/
void Animal::initAI(unsigned pause, unsigned turn){
	pauseChance = pause;
	turnChance = turn;
}

/**
	Test if a random number between 0 and 100 is
	<= a given number
	@param chance the probability out of 100
	@return true if <= chance, false otherwise
*/
bool attempt(unsigned chance){
	return (rand() % 100) <= chance;
}

/**
	Perform actions based on predetermined traits
*/
void Animal::followAI(){
	if(attempt(pauseChance)){			//Pause or continue?
		return;							//Decided to pause; do nothing
	}

	if(attempt(turnChance)){			//Turn or continue straight?
		int steps = rand() % 3;			//How far
		int dir = pow(-1, rand() % 6);	//Which direction
		rotate(steps * dir);			//Perform turn
	} else {
		advance(1);						//Move forward
	}
}

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
	Position np = {nx, ny, pos.z};

	if(canMove(steps, np)){
		pos.x = nx;
		pos.y = ny;
	}
}

/**
	Test a new position against the extreme boundaries of
	this Animal
	@param direction positive for forward movement, negative for reverse
	@param p the desired position
	@return true if it is possible to move to the given position
*/
bool Animal::canMove(int direction, Position p){
	int d = 0;
	float dist = sqrt(pow(p.x - pos.x, 2) + pow(p.y - pos.y, 2));

	float phi = 0;
	if(direction > 0){				//Moving forward
		phi = atan(abs(frontOffset / rightOffset));
		d = 1;
	} else if(direction < 0){		//Moving backwards
		phi = atan(abs(rearOffset / rightOffset));
		d = -1;
	}	//Distance to furthest point from center in direction of movement
	float diag = abs(rightOffset / cos(phi));

	//Calculate where the outer bounds of this Animal would be
	float hC = diag + dist;
	float xC = hC * cos(forward) * d;
	float yC = hC * sin(forward) * d;

	Position testPos = {pos.x + xC, pos.y + yC, pos.z};
	return env->isInBounds(testPos) && !(willCollide(this, testPos));
}

/**
	Determines whether or not this Animal contains the given point
	@param p the point in question
	@return true if it is within the bounds of this Animal, false otherwise
*/
bool Animal::containsPosition(Position p){
	Position min = {pos.x + leftOffset, pos.y + rearOffset, pos.z};
	Position max = {pos.x + rightOffset, pos.y + frontOffset, pos.z};
	bool minCheck = (p.x >= min.x) && (p.y >= min.y) && (p.z >= min.z);
	bool maxCheck = (p.x <= max.x) && (p.y <= max.y) && (p.z <= max.z);
	return minCheck && maxCheck;
}

/**
	Determines whether or not a given animal will collide with another at a given point
	@param a a pointer to the Animal that is being tested
	@param p the position that a is trying to move to
	@return true if a will collide with another animal, false otherwise
*/
bool Animal::willCollide(Animal* a, Position p){
	std::vector<Animal>* animals = (std::vector<Animal>*) env->getContents();
	for(unsigned x = 0; x < animals->size(); x++){
		if(a != &(animals->at(x))){
			if(animals->at(x).containsPosition(p)){
				return true;
			}
		}
	}
	return false;
}
/**
	Perform transformations and call display list to display this Animal
	*/
void Animal::display(){
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	glRotatef(radToDeg(forward) - 90, 0, 0, 1);
	glCallList(getDisplayID());
	glPopMatrix();
}