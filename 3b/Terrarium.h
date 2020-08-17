/**
	A terrarium in which animals can exist
	@author Douglas Skrypa
	@version 2014.04.09
*/

#ifndef TERRARIUM_H
#define TERRARIUM_H

#include <vector>
#include "Env3D.h"
#include "TerrEntity.h"
#include "TerrWall.h"
#include "Animal.h"
#include "Bug.h"
#include "Penguin.h"

#define WALL_THICKNESS 1

class Terrarium
{
	private:
		Env3D* env;
		std::vector<TerrEntity> entities;	//Store occupying entities
		std::vector<Animal> animals;		//Store occupying animals
		float xBoundLow, xBoundHigh, yBoundLow, yBoundHigh;
	public:
		Terrarium();
		Terrarium(Env3D*);
		void populate();
		void display();
		void tryMove(Animal*);
		std::vector<TerrEntity>* getEntities();
};
#endif
