#include "Wire.h"

Wire::Wire(){}

Wire::Wire(const int iid, const int t, const int xa, const int ya, const int xb, const int yb, const float ir, const float ig, const float ib, const float split)
{
	if((t < 0) || (t > 3)){
		throw t;
	}
	id = iid;
	type = t;
	startX = xa;
	startY = ya;
	endX = xb;
	endY = yb;
	r = ir;
	g = ig;
	b = ib;
	splitPoint = split;

	makeWire();
	
	glNewList(id, GL_COMPILE);
		glColor3f(r, g, b);
		glCallList(10000 + id);
	glEndList();
}

/**
	Draw a Wire between the given points, with the given layout type and color
*/
void Wire::makeWire()
{
	int xDist = endX - startX;
	int yDist = endY - startY;
	int xA = xDist * splitPoint;
	int yA = yDist * splitPoint;

	glNewList(10000 + id, GL_COMPILE);
		glTranslatef(startX, startY, 0);
		glBegin(GL_LINES);
			glVertex2f(0, 0);
			switch(type){
				case LAYOUT_XY:
					glVertex2f(xDist, 0);
					glVertex2f(xDist, 0);
					break;				
				case LAYOUT_YX:
					glVertex2f(0, yDist);
					glVertex2f(0, yDist);
					break;
				case LAYOUT_XYX:
					glVertex2f(xA, 0);
					glVertex2f(xA, 0);
					glVertex2f(xA, yDist);
					glVertex2f(xA, yDist);
					break;
				case LAYOUT_YXY:
					glVertex2f(0, yA);
					glVertex2f(0, yA);
					glVertex2f(xDist, yA);
					glVertex2f(xDist, yA);
					break;
			}
			glVertex2f(xDist, yDist);
		glEnd();
		glTranslatef(-startX, -startY, 0);
	glEndList();
}
