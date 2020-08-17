/**
	A terminal for logic gates.
	@author Douglas Skrypa
	@version 2014.03.09
*/

#include "Terminal.h"

Terminal::Terminal(){}

Terminal::Terminal(const int posX, const int posY, const int ioType, const int iid)
{
	x = posX;
	y = posY;
	type = ioType;
	width = 15;
	height = 15;
	id = iid;
	highlighted = false;

	//Terminal outline
	glNewList(10000+id, GL_COMPILE);
		glRectf(0, 0, width, height);
	glEndList();

	//Terminal body
	glNewList(20000+id, GL_COMPILE);
		glRectf(1, 1, width-1, height-1);
	glEndList();

	makeTerminal();
}

/**
	Returns the type of this Terminal (input or output)
*/
int Terminal::getType()
{
	return type;
}

/**
	Returns true if this Terminal is activated (highlighted)
*/
bool Terminal::isActivated()
{
	return highlighted;
}

/**
	<<<Private>>>
	Finalizes the glList that represents this Terminal based on the state of
	being highlighted or not.
*/
void Terminal::makeTerminal()
{
	glNewList(id, GL_COMPILE);
		glTranslatef(x, y, 0);
		glColor3f(1, 1, 1);
		glCallList(10000+id);
		if(highlighted){
			glColor3f(1, 1, 1);
		} else {
			glColor3f(0, 0, 0);
		}
		glCallList(20000+id);
		glTranslatef(-x, -y, 0);
	glEndList();
}

/**
	Sets the highlighted state of this Terminal to true.
*/
void Terminal::activate()
{
	highlighted = true;
	makeTerminal();
}

/**
	Sets the highlighted state of this Terminal to false.
*/
void Terminal::deactivate()
{
	highlighted = false;
	makeTerminal();
}
