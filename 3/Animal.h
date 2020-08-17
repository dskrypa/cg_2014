/**
	Animal that exists inside a terrarium
	@author Douglas Skrypa
	@version 2014.04.09
*/

#ifndef ANIMAL_H
#define ANIMAL_H

#include "TerrEntity.h"
#include <math.h>

class Animal: public TerrEntity
{
	protected:
		float movementSpeed;
		float xDir, yDir;
	public:
		Animal();
		Animal(Position p, Dimensions d);
		float getMovementSpeed();
		void updatePosition(float, float, float);
		void attemptMove(float, float, float, float);
};
#endif
