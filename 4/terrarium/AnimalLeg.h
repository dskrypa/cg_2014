/**
	A moving Animal leg
	@author Douglas Skrypa
	@version 2014.05.09
*/

#ifndef ANIMALLEG_H
#define ANIMALLEG_H

#include "TerrEntity.h"

enum LegState {STILL = 0, EXTENDED = 1, BACK = -1};

class AnimalLeg: public TerrEntity
{
	private:
		LegState state;				//Current state of this AnimalLeg
		float forward;				//Angle between x axis and direction Animal is facing
		float swingAngle;			//Max angle between STILL & EXTENDED in either direction
		int swingDirection;			//Positive or negative swing direction
		void initDisplay();
	public:
		AnimalLeg();
		AnimalLeg(Position p);
		LegState getLegState();
		void display();
};
#endif