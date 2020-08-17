/**
	Animal that exists inside a terrarium
	@author Douglas Skrypa
	@version 2014.05.09
*/

#ifndef ENV3D_H
#define ENV3D_H

#include <vector>
#include "common.h"

class Env3D {
	private:
		float targetFps;					//Target frame rate
		float windowWidth, windowHeight;	//Window dimensions
		Position min, max;					//Min/max XYZ bounds of environment
		void* contents;
	public:
		Env3D();
		Env3D(float fps, float wWidth, float wHeight, Position pMin, Position pMax);
		void setContents(void* o);
		void* getContents();
		bool isInBounds(Position p);
		void setTargetFps(float fps);
		void setWinSize(float w, float h);
		void setMinPoint(Position p);
		void setMaxPoint(Position p);
		float getBoundedWidth();
		float getBoundedLength();
		float getBoundedHeight();
		float getTargetFps();
		float getWinWidth();
		float getWinHeight();
		Position getMinPoint();
		Position getMaxPoint();
};
#endif
