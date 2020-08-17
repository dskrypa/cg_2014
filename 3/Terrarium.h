/**
	A terrarium in which animals can exist
	@author Douglas Skrypa
	@version 2014.04.09
*/

#ifndef TERRARIUM_H
#define TERRARIUM_H

#include <vector>
#include "TerrEntity.h"
#include "TerrWall.h"
#include "Animal.h"
#include "Bug.h"
#include "Penguin.h"

#define WALL_THICKNESS 1

class Terrarium
{
	private:
		std::vector<TerrEntity> entities;	//Store occupying entities
		std::vector<Animal> animals;		//Store occupying animals
		float xBoundLow, xBoundHigh, yBoundLow, yBoundHigh;
	public:
		Terrarium();
		Terrarium(float, float, float);
		void populate();
		void display();
		void tryMove(Animal*);
		std::vector<TerrEntity>* getEntities();
};
#endif
