/**
	A Character is a BoardObject that is able to move, and is able to travel
	automatically at a given speed.
	@author Douglas Skrypa
	@version 2014.02.17
*/

#include "Character.h"
#include "BoardObject.h"

/**
	Constructor with default values.
*/
Character::Character()
{
	x = 0;
	y = 0;
	height = 50;
	width = 50;
	movementSpeed = 5;
}

/**
	Constructor for a custom position.
	@param x the x value of a point
	@param y the y value of a point
*/
Character::Character(double x, double y)
{
	this->x = x;
	this->y = y;
	height = 50;
	width = 50;
	movementSpeed = 5;
}

/**
	Travel the given distance along the x axis
	@param d the amount by which to augment this Character's position's x value
*/
void Character::addX(double d)
{
	x += d;
}

/**
	Travel the given distance along the y axis
	@param d the amount by which to augment this Character's position's y value
*/
void Character::addY(double d)
{
	y += d;
}

/**
	Set the speed at which this Character will move
	@param s a new speed
*/
void Character::setMovementSpeed(int s)
{
	movementSpeed = s;
}

/**
	Increases this Character's speed by 1, to a max of 12, and redraws.
*/
void Character::incSpeed()
{
	if(++movementSpeed > 12){
		movementSpeed = 12;
	}
	glutPostRedisplay();
}

/**
	Decreases this Character's speed by 1, to a min of 0, and redraws.
*/
void Character::decSpeed()
{
	if(--movementSpeed < 0){
		movementSpeed = 0;
	}
	glutPostRedisplay();
}

/**
	Returns this Character's movement speed.
	@return this Character's movement speed
*/
int Character::getSpeed()
{
	return movementSpeed;
}

/**
	Draws the representation of this Character using GLUT.
	The color is determined by the current speed.
*/
void Character::display()
{
	glBegin(GL_POLYGON);
		glColor3f(movementSpeed/12.0, 0.0, 1-(movementSpeed/12.0));
		glVertex2f(0.0+x, 0.0+y);
		glVertex2f(0.0+x, height+y);
		glVertex2f(width+x, height+y);
		glVertex2f(width+x, 0.0+y);
	glEnd();
}

/**
	Returns this Character's height.
	@return height of this Character
*/
double Character::getHeight()
{
	return height;
}

/**
	Returns this Character's width.
	@return width of this Character
*/
double Character::getWidth()
{
	return width;
}
