/**
	An object that can be placed inside a Terrarium
	@author Douglas Skrypa
	@version 2014.05.09
*/

#ifndef TERRENTITY_H
#define TERRENTITY_H

//GLUT is in a different place on mac vs linux/pc
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <string>
#include "common.h"

class TerrEntity {
	private:
		unsigned dispID;
	protected:
		Position pos;
		Dimensions dim;
		float frontOffset, rearOffset, leftOffset, rightOffset;
		void generateDisplayID();
		void initEntity(Position p, Dimensions d, float n, float s, float w, float e);
	public:
		TerrEntity();
		TerrEntity(unsigned id, Position p, Dimensions d);
		unsigned getDisplayID();
		void setPos(Position p);
		void setDims(Dimensions d);
		Position* getPos();
		float getDistance(TerrEntity* other);
		float getDistance(Position p);
		std::string getPosStr();
		std::string getDimStr();
		std::string toString();
};
#endif