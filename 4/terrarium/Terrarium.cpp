/**
	A terrarium in which animals can exist
	@author Douglas Skrypa
	@version 2014.05.09
*/

#include <iostream>
#include "Terrarium.h"
#include "TerrEntity.h"
#include "Animal.h"
#include "Bug.h"

Terrarium::Terrarium(){}

/**
	Construct a Terrarium with a specific width, height, and depth.
*/
Terrarium::Terrarium(Env3D* environment){
	//std::cout<<"Terrarium(): Constructing... h="<<height<<" w="<<width<<" d="<<depth<<std::endl;

	env = environment;
	env->setContents(&animals);
	Position min = env->getMinPoint();
	Position max = env->getMaxPoint();
	Dimensions d = {env->getBoundedWidth(), env->getBoundedLength(), env->getBoundedHeight()};

	//Build floor + frame list
	int floorID = glGenLists(1);
	glNewList(floorID, GL_COMPILE);
		//Floor
		glColor3ub(200, 200, 0);
		glBegin(GL_QUADS);
			glVertex3f(min.x, min.y, 0.0f);
			glVertex3f(min.x, max.y, 0.0f);
			glVertex3f(max.x, max.y, 0.0f);
			glVertex3f(max.x, min.y, 0.0f);
		glEnd();

		//Frame
		glColor3ub(255, 255, 255);
		glTranslatef(0.0f, 0.0f, d.h / 2.0f);
		glScalef(d.w, d.l, d.h);
		glutWireCube(1.0f);
	glEndList();

	TerrEntity floor = TerrEntity(floorID, min, d);
	addEntity(floor);
}

/**
	Populates this Terrarium with TerrEntities.
	*/
void Terrarium::populate(){
	Bug b1 = Bug(env, {2.0f, 3.0f, 1.05f});
	Bug b2 = Bug(env, {5.0f, 8.0f, 1.05f});
	addAnimal(b1);
	addAnimal(b2);
}

/**
	Draw the walls and contents of this Terrarium
*/
void Terrarium::display(){
	std::vector<Animal>* animals = getAnimals();
	for(unsigned x = 0; x < animals->size(); x++){
		animals->at(x).followAI();
		animals->at(x).display();
	}

	std::vector<TerrEntity>* entities = getEntities();
	for(unsigned x = 0; x < entities->size(); x++){
		glPushMatrix();
		glCallList(entities->at(x).getDisplayID());
		glPopMatrix();
	}
}

/**
	Add an entity to this 3D environment
	@param te the TerrEntity to add
	*/
void Terrarium::addEntity(TerrEntity te){
	entities.push_back(te);
}

/**
	Add an animal to this 3D environment
	@param a the animal to add
	*/
void Terrarium::addAnimal(Animal a){
	animals.push_back(a);
}

/**
	Obtain a pointer to the vector containing the entities in this 3D environment
	@return std::vector<TerrEntity>* containing the entities in this 3D environment
	*/
std::vector<TerrEntity>* Terrarium::getEntities(){
	return &entities;
}

/**
	Obtain a pointer to the vector containing the animals in this 3D environment
	@return std::vector<Animal>* containing the animals in this 3D environment
	*/
std::vector<Animal>* Terrarium::getAnimals(){
	return &animals;
}