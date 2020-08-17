/**
	A Terrarium Wall
	@author Douglas Skrypa
	@version 2014.04.09
*/

#ifndef TERRWALL_H
#define TERRWALL_H

#include "TerrEntity.h"

class TerrWall: public TerrEntity
{
	private:
		float RGB[3];
	public:
		TerrWall();
		TerrWall(Position, Dimensions, unsigned char, unsigned char, unsigned char);
};
#endif

