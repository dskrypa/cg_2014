/**
	Animal that exists inside a terrarium
	@author Douglas Skrypa
	@version 2014.04.09
*/

#ifndef ENV3D_H
#define ENV3D_H

#include <math.h>

struct Position		{float x, y, z, w;};
struct Dimensions	{float w, l, h;};

class Env3D {
	private:
		float targetFps;					//Target frame rate
		float windowWidth, windowHeight;	//Window dimensions
		Position min, max;					//Min/max XYZ bounds of envrionment
	public:
		Env3D();
		Env3D(float, float, float, Position, Position);
		
		void setTargetFps(float);
		void setWinSize(float, float);
		void setMinPoint(Position);
		void setMaxPoint(Position);
		
		float getBoundedWidth();
		float getBoundedLength();
		float getBoundedHeight();
		
		float getTargetFps();
		float getWinWidth();
		float getWinHeight();
		Position getMinPoint();
		Position getMaxPoint();
		bool isInBounds(Position);		//Ask env if a given point is in bounds
		
		static float degToRad(float degrees){
			return degrees * M_PI / 180.0f;
		}

		static float radToDeg(float radians){
			return radians * 180.0f / M_PI;
		}
};
#endif
