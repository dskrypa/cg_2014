/**
	A clickable icon used to execute an action.
	@author Douglas Skrypa
	@version 2014.03.09
*/

#include "Icon.h"

/*
	Font options: (ASCII chars 32 - 127 only)
	GLUT_STROKE_ROMAN:		Roman Simplex font (proportional)
	GLUT_STROKE_MONO_ROMAN:	Roman Simplex font (monospaced)
*/
#define FONT GLUT_STROKE_ROMAN

Icon::Icon(){}

Icon::Icon(const std::string text, const int posX, const int posY, const float iWidth, const float iHeight, const int iid)
{
	buttonText = text;
	x = posX;
	y = posY;
	width = iWidth;
	height = iHeight;
	id = iid;
	highlighted = false;

	//Determine scale for text based on Icon width and width of given text
	float scale = (width * 0.9) / getTextWidth((const char*)buttonText.c_str());

	//Icon outline
	glNewList(10000 + id, GL_COMPILE);
		glTranslatef(x, y, 0);
		glRectf(0, 0, width, height);
	glEndList();

	//Icon text, centered within icon
	glNewList(11000 + id, GL_COMPILE);
		glTranslatef((width * 0.05), (height * 0.05), 0);	// relative
		glScalef(scale, scale, 0);
		addText((const char*)buttonText.c_str());
	glEndList();

	makeIcon();
}

/**
	Swaps the text and background colors of this Icon
*/
void Icon::invertColors()
{
	highlighted = !highlighted;
	makeIcon();
}

/**
	Sets the highlighted state of this Icon to true.
*/
void Icon::activate()
{
	highlighted = true;
	makeIcon();
}

/**
	Sets the highlighted state of this Icon to false.
*/
void Icon::deactivate()
{
	highlighted = false;
	makeIcon();
}

/**
	<<<Private>>>
	Finalizes the glList that represents this Icon based on the state of being
	highlighted or not.
*/
void Icon::makeIcon()
{
	glNewList(id, GL_COMPILE);
		if(highlighted){
			glColor3f(0, 0, 1);
		} else {
			glColor3f(1, 1, 1);
		}
		glCallList(10000 + id);
		if(highlighted){
			glColor3f(1, 1, 1);
		} else {
			glColor3f(0, 0, 1);
		}
		glCallList(11000 + id);
	glEndList();
}

/**
	@return this Icon's text and list ID
*/
std::string Icon::getText()
{
	std::stringstream ss;
	ss<<buttonText<<"\t"<<id;
	return ss.str();
}

/**
	<<<Private>>>
	Determines the total display width of the given string
	@param text a character array (string) to be measured
	@return the total width of the given string in the active font (in pixels)
*/
int Icon::getTextWidth(const char* text)
{
	int totWidth = 0;
	for(unsigned int x = 0; x < sizeof(text); x++){
		totWidth += glutStrokeWidth(FONT, text[x]);
	}
	return totWidth;
}

/**
	<<<Private>>>
	Adds the given text to this Icon
	Iterates through each character in the given string, and draws that char
	using GLUT.
	@param text a character array (string) to display on this Icon
*/
void Icon::addText(const char* text)
{
	for(unsigned int x = 0; x < sizeof(text); x++){
		glutStrokeCharacter(FONT, text[x]);
	}
}
