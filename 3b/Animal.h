/**
	Animal that exists inside a terrarium
	@author Douglas Skrypa
	@version 2014.04.09
*/

#ifndef ANIMAL_H
#define ANIMAL_H

#include "TerrEntity.h"

class Animal: public TerrEntity
{
	protected:
		float moveSpeedSecs, spinSpeedSecs;
		float forward;
		Env3D* env;
	public:
		Animal();
		Animal(Position p, Dimensions d);
		float getMoveSpeedPerFrame();
		float getSpinSpeedPerFrame();
		void updatePosition(float, float, float);
		void attemptMove(float, float, float, float);
		void rotate(int);
		void advance(int);
		void display();
		float asDeg(float);
};
#endif
