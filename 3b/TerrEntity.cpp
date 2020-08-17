/**
	An object that can be placed inside a Terrarium
	@author Douglas Skrypa
	@version 2014.04.09
*/

#include "TerrEntity.h"
#include <sstream>

TerrEntity::TerrEntity(){}

TerrEntity::TerrEntity(unsigned const int id){
	dispID = id;
}

/**
	Generates and stores an available display list ID for this TerrEntity
*/
void TerrEntity::generateDisplayID(){
	dispID = glGenLists(1);
}

/**
	Retrieve the ID for the display list that represents this TerrEntity
	@return int display list ID
*/
unsigned int TerrEntity::getDisplayID(){
	return dispID;
}

/**
	Calculate the distance between this TerrEntity and other
	@param other a pointer to another TerrEntity
	@return float distance between TerrEntities
*/
float TerrEntity::getDistance(TerrEntity *other){
	return -1;
}

/**
	Set the position of bottom-left-front point of this TerrEntity
	@param x the x-axis coordinate
	@param y the y-axis coordinate
	@param z the z-axis coordinate
*/
void TerrEntity::setPos(float x, float y, float z){
	pos.x = x;
	pos.y = y;
	pos.z = z;
}

/**
	Set the dimensions of this TerrEntity
	@param w the width
	@param l the length / depth
	@param h the height
*/
void TerrEntity::setDims(float w, float l, float h){
	dim.w = w;
	dim.l = l;
	dim.h = h;
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
	ss<<"("<<pos.x<<", "<<pos.y<<", "<<pos.z<<")";
	return ss.str();
}

/**
	Construct a string representation of this TerrEntity's dimensions
	@return std::string representation of dimensions
*/
std::string TerrEntity::getDimStr(){
	std::stringstream ss;
	ss<<"w x h x l: "<<dim.w<<" x "<<dim.h<<" x "<<dim.l;
	return ss.str();
}

/**
	Construct a string representation of this TerrEntity including position,
	dimension, and ID data.
	@return std::string representation of this TerrEntity
*/
std::string TerrEntity::toString(){
	std::stringstream ss;
	ss<<"TerrEntity"<<"(ID: "<<dispID<<") @ "<<getPosStr()<<"\t"<<getDimStr();
	return ss.str();
}

/**
	Retrieve this TerrEntity's position coordinates
	@return int* a pointer to an array of format [X, Y, Z]
*/
Position* TerrEntity::getPos(){
	return &pos;
}
