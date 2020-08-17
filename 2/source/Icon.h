/**
	A clickable icon used to execute an action.
	Extends Clickable.
	@author Douglas Skrypa
	@version 2014.03.09
*/

#ifndef ICON_H
#define ICON_H

#include <string>
#include <sstream>
#include <iostream>
#include "Clickable.h"

class Icon: public Clickable
{
	private:
		std::string buttonText;			//Text displayed on this Icon
		bool highlighted;				//Highlighted state
		int getTextWidth(const char*);	//Returns the width of buttonText in px
		void addText(const char*);		//Adds the given text to this Icon
		void makeIcon();				//Finalize this Icon's glList
	public:
		Icon();							//Default constructor
		Icon(const std::string, const int, const int, const float, const float, const int);
		std::string getText();			//Returns this Icon's text
		void invertColors();			//Swaps text & background colors
		void activate();				//Sets highlighted to true
		void deactivate();				//Sets highlighted to false
};
#endif
