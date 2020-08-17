/**
	A clickable object on a plane.
	@author Douglas Skrypa
	@version 2014.03.09

	Clickable is intended to be an interface for objects to be drawn for
	Homework 2, which have common properties.
*/

#ifndef CLICKABLE_H
#define CLICKABLE_H

#include <GLUT/glut.h>

class Clickable{
	protected:
		int x, y;						//x, y coordinates of bottom-left corner
		float width, height;			//width & height
		int id;							//Unique identifier
	public:
		Clickable();					//Default constructor
		Clickable(const int, const int, const float, const float, const int);
		bool wasClicked(int, int);		//Returns true if clicked, else false
		int getId();					//Returns unique identifier
		int getX();						//Returns the x-coordinate
		int getY();						//Returns the y-coordinate
};
#endif
