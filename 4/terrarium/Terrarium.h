/**
	A terrarium in which animals can exist
	@author Douglas Skrypa
	@version 2014.04.09
	*/

#ifndef TERRARIUM_H
#define TERRARIUM_H

#include "Env3D.h"
#include "Animal.h"

#define WALL_THICKNESS 1

class Terrarium {
	private:
		Env3D* env;
		std::vector<TerrEntity> entities;	//Store occupying entities
		std::vector<Animal> animals;		//Store occupying animals
	public:
		Terrarium();
		Terrarium(Env3D*);
		void populate();
		void display();
		void addEntity(TerrEntity te);
		void addAnimal(Animal a);
		std::vector<TerrEntity>* getEntities();
		std::vector<Animal>* getAnimals();
};
#endif
