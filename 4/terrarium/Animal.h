/**
	Animal that exists inside a terrarium
	@author Douglas Skrypa
	@version 2014.05.09
*/

#ifndef ANIMAL_H
#define ANIMAL_H

#include <vector>
#include "Env3D.h"
#include "TerrEntity.h"
#include "AnimalLeg.h"

class Animal: public TerrEntity
{
	protected:
		float moveSpeedSecs, spinSpeedSecs;		//Movement/Spin speed in terms of time
		float forward;							//Angle between x axis and direction Animal is facing
		Env3D* env;								//Pointer to the Env3D that this Animal exists in
		unsigned pauseChance, turnChance;		//1-100 chance of action in AI
		std::vector<AnimalLeg> legs;			//Array of legs
		void initAnimal(Env3D* envr, float faceAng, float moves, float spins);
		void initAI(unsigned pause, unsigned turn);
	public:
		Animal();
		Animal(Position p, Dimensions d);
		void followAI();
		float getMoveSpeedPerFrame();
		float getSpinSpeedPerFrame();
		bool canMove(int direction, Position p);
		bool containsPosition(Position p);
		bool willCollide(Animal* a, Position p);
		void rotate(int);
		void advance(int);
		void display();
};
#endif
