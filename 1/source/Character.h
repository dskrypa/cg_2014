/**
	A Character is a BoardObject that is able to move, and is able to travel
	automatically at a given speed.
	@author Douglas Skrypa
	@version 2014.02.17
*/

#ifndef CHARACTER_H
#define CHARACTER_H

#include "BoardObject.h"

class Character: public BoardObject
{
	private:
		int movementSpeed;
	public:
		Character();
		Character(double, double);
		void addX(double);
		void addY(double);
		void setMovementSpeed(int);
		void incSpeed();
		void decSpeed();
		int getSpeed();
		void display();
		double getHeight();
		double getWidth();
};
#endif
