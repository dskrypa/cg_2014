/**
	An object that can be placed inside a Terrarium
	@author Douglas Skrypa
	@version 2014.05.09
*/

#include <sstream>
#include "TerrEntity.h"


TerrEntity::TerrEntity(){}

TerrEntity::TerrEntity(unsigned id, Position p, Dimensions d){
	dispID = id;
	initEntity(p, d, 0, 0, 0, 0);
}

/**
	Generates and stores an available display list ID for this TerrEntity
*/
void TerrEntity::generateDisplayID(){
	dispID = glGenLists(1);
}

/**
	Initialize common variables to TerrEntities
*/
void TerrEntity::initEntity(Position p, Dimensions d, float n, float s, float w, float e){
	setPos(p);
	setDims(d);
	frontOffset = n;
	rearOffset = s;
	leftOffset = w;
	rightOffset = e;
}

/**
	Retrieve the ID for the display list that represents this TerrEntity
	@return display list ID
*/
unsigned TerrEntity::getDisplayID(){
	return dispID;
}

/**
	Calculate the distance between this TerrEntity and other
	@param other a pointer to another TerrEntity
	@return float distance between TerrEntities
*/
float TerrEntity::getDistance(TerrEntity* other){
	return -1;		//TODO Implement
}

/**
	Calculate the distance between this TerrEntity and a given position
	@param p a position
	@return float distance between TerrEntities
*/
float TerrEntity::getDistance(Position p){
	return -1;		//TODO Implement
}

/**
	Set the position of bottom-left-front point of this TerrEntity
	@param p the position
*/
void TerrEntity::setPos(Position p){
	pos = p;
}

/**
	Set the dimensions of this TerrEntity
	@param d the dimensions
*/
void TerrEntity::setDims(Dimensions d){
	dim = d;
}

/**
	Construct a string representation of this TerrEntity's position
	@return std::string representation of current position
*/
std::string TerrEntity::getPosStr(){
	std::stringstream ss;
	ss << "(" << pos.x << ", " << pos.y << ", " << pos.z << ")";
	return ss.str();
}

/**
	Construct a string representation of this TerrEntity's dimensions
	@return std::string representation of dimensions
*/
std::string TerrEntity::getDimStr(){
	std::stringstream ss;
	ss << "w x h x l: " << dim.w << " x " << dim.h << " x " << dim.l;
	return ss.str();
}

/**
	Construct a string representation of this TerrEntity including position,
	dimension, and ID data.
	@return std::string representation of this TerrEntity
*/
std::string TerrEntity::toString(){
	std::stringstream ss;
	ss << "TerrEntity" << "(ID: " << dispID << ") @ " << getPosStr() << "\t" << getDimStr();
	return ss.str();
}

/**
	Retrieve this TerrEntity's position coordinates
	@return a pointer to its Position
*/
Position* TerrEntity::getPos(){
	return &pos;
}
