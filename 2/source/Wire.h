/**
	A wire.
	@author Douglas Skrypa
	@version 2014.03.09
*/

#ifndef WIRE_H
#define WIRE_H

#include <GLUT/glut.h>

#define LAYOUT_XY	0
#define LAYOUT_YX	1
#define LAYOUT_XYX	2
#define LAYOUT_YXY	3

class Wire{
	private:
		int type, id;
		int startX, startY, endX, endY;
		float r, g, b;
		float splitPoint;
		void makeWire();
	public:
		Wire();
		Wire(const int, const int, const int, const int, const int, const int, const float, const float, const float, const float);
};
#endif

