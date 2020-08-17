/**
	A BoardObject is an object that can be drawn on a Board using GLUT.
	The point that a BoardObject stores for its position is its bottom-left
	corner.
	@author Douglas Skrypa
	@version 2014.02.17
*/

#ifndef BOARDOBJECT_H
#define BOARDOBJECT_H

#include <GLUT/glut.h>

class BoardObject
{
	protected:
		double x, y;
		double height, width;
	public:
		BoardObject();
		BoardObject(double, double, double, double);
		double getX();
		double getY();
		void display();
		bool contains(double, double);
		bool willCollideWith(BoardObject&, int);
};
#endif
