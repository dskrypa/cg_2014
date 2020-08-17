#include "Clickable.h"

Clickable::Clickable(){}

Clickable::Clickable(const int posX, const int posY, const float iWidth, const float iHeight, const int iid)
{
	x = posX;
	y = posY;
	width = iWidth;
	height = iHeight;
	id = iid;
}

/**
	Determines whether or not this Icon was clicked on
	@param cx the x-value of the point that was clicked on
	@param cy the y-value of the point that was clicked on
	@return true if the point (x, y) falls within the bounds of this Icon
*/
bool Clickable::wasClicked(int cx, int cy)
{
	bool inColumn, inRow;
	inColumn = (x <= cx) && (cx <= (x + width));
	inRow = (y <= cy) && (cy <= (y + height));
	/*std::cout<<"Lower-left corner: ("<<x<<", "<<y<<")\tclick point: ("<<cx<<", "<<cy<<")"<<std::endl;
	std::cout<<"inCol: "<<inColumn<<" inRow: "<<inRow<<std::endl;
	if(inColumn && inRow){
		std::cout<<"I was clicked"<<std::endl;
		return true;
	} else {
		std::cout<<"I was not clicked"<<std::endl;
		return false;
	}*/
	return inColumn && inRow;
}

/**
	Return the ID of this object
*/
int Clickable::getId()
{
	return id;
}

/**
	Return this object's x-coordinate
*/
int Clickable::getX()
{
	return x;
}

/**
	Return this object's y-coordinate
*/
int Clickable::getY()
{
	return y;
}
