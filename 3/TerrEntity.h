/**
	An object that can be placed inside a Terrarium
	@author Douglas Skrypa
	@version 2014.04.09
*/

#ifndef TERRENTITY_H
#define TERRENTITY_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <string>
#include <sstream>

struct Position		{float x, y, z;};
struct Dimensions	{float w, l, h;};

class TerrEntity
{
	private:
		unsigned int dispID;
	protected:
		Position pos;
		Dimensions dim;
		void generateDisplayID();
	public:
		TerrEntity();
		TerrEntity(unsigned const int);
		unsigned int getDisplayID();
		void setPos(Position);
		void setDims(Dimensions);
		void setPos(float, float, float);
		void setDims(float, float, float);
		Position* getPos();
		float getDistance(TerrEntity*);
		std::string getPosStr();
		std::string getDimStr();
		std::string toString();
};
#endif
