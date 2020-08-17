/**
	A logic gate.
	@author Douglas Skrypa
	@version 2014.03.09
*/

#include "LogicGate.h"

LogicGate::LogicGate(){}

LogicGate::LogicGate(const int type, const int posX, const int posY, const int iid)
{
	gateType = type;
	x = posX;
	y = posY;
	height = 100;
	id = iid;

	switch(gateType){
		case AND_GATE:
			//2 inputs
			makeAndGate();
			break;
		case OR_GATE:
			//2 inputs
			makeOrGate();
			break;
		case NOT_GATE:
			//Only one input
			makeNotGate();
			break;
		default:
			throw type;
	}

	makeTerminals();

	glNewList(id, GL_COMPILE);
		glColor3f(1, 1, 1);
		glCallList(10000 + id);
		glCallList(20000 + id);
	glEndList();
}

/**
	Returns true if the ID of this LogicGate is the same as the ID of otherGate
*/
bool LogicGate::equals(LogicGate* otherGate)
{
	return getId() == otherGate->getId();
}

/**
	Draw an And gate
*/
void LogicGate::makeAndGate()
{
	width = 50;
	glNewList(10000 + id, GL_COMPILE);
		glTranslatef(x, y, 0);
		glBegin(GL_POLYGON);
			/*
				Draw a semi-circle using Pythagoras' theorem, a² + b² = c²,
				where c is the hypotenuse (also the radius), b is the relative
				position on the y-axis, and a is the relative position on the
				x-axis.  One vertex is created for each pixel of height.
			*/
			for(int n = 0; n <= height; n++){
				float b = (height / 2) - n;
				float a = sqrt(pow(width, 2) - pow(b, 2));
				glVertex2f(a, (height / 2) + b);
			}
		glEnd();
		glTranslatef(-x, -y, 0);
	glEndList();
}

/**
	Draw an Or gate
*/
void LogicGate::makeOrGate()
{
	width = height;
	float dy = height / 4;
	float dx = width / 2;

	//Hexagon: Filled-in
	glNewList(10000 + id, GL_COMPILE);
		glTranslatef(x, y, 0);
		glBegin(GL_POLYGON);
			glVertex2f(0, dy);
			glVertex2f(0, 3 * dy);
			glVertex2f(dx, height);
			glVertex2f(width, 3 * dy);
			glVertex2f(width, dy);
			glVertex2f(dx, 0);
		glEnd();
		glTranslatef(-x, -y, 0);
	glEndList();
}

/**
	Draw a Not gate
*/
void LogicGate::makeNotGate()
{
	width = 50;
	glNewList(10000 + id, GL_COMPILE);
		glTranslatef(x, y, 0);
		glBegin(GL_POLYGON);
			glVertex2f(0, 0);
			glVertex2f(0, height);
			glVertex2f(width, height/2);
		glEnd();
		glTranslatef(-x, -y, 0);
	glEndList();
}

/**
	Draw relevant Terminals and their connections
*/
void LogicGate::makeTerminals()
{
	float outX = x + width + 20;
	float outY = y + (height / 2);
	float in1X = x - 20;
	float in2X = x - 20;
	float in1Y, in2Y;

	if(multipleInputs()){
		//2 inputs
		in1Y = y + (height / 3);
		in2Y = y + (2 * height / 3);
		in2 = Terminal(in2X-15, in2Y-7, TERM_INPUT, 24000+id);
	} else {
		//Only one input
		in1Y = y + (height / 2);
	}

	out = Terminal(outX, outY-7, TERM_OUTPUT, 22000+id);
	in1 = Terminal(in1X-15, in1Y-7, TERM_INPUT, 23000+id);

	glNewList(21000 + id, GL_COMPILE);
		glBegin(GL_LINES);
			glVertex2f(outX-21, outY);
			glVertex2f(outX, outY);

			glVertex2f(in1X, in1Y);
			glVertex2f(in1X+20, in1Y);

			if(gateType != NOT_GATE){
				glVertex2f(in2X, in2Y);
				glVertex2f(in2X+20, in2Y);
			}
		glEnd();
	glEndList();

	glNewList(20000 + id, GL_COMPILE);
		glCallList(21000 + id);
		glCallList(22000 + id);
		glCallList(23000 + id);

		if(multipleInputs()){
			glCallList(24000 + id);
		}
	glEndList();
}

/**
	Return the Terminal with the given index
*/
Terminal* LogicGate::get(const int term)
{
	switch(term){
		case TERM_OUTPUT:
			return &out;
		case TERM_INPUT1:
			return &in1;
		case TERM_INPUT2:
			if(!multipleInputs()){
				throw term;
			}
			return &in2;
		default:
			throw term;
	}
}

/**
	Return true if this LogicGate has multiple input Terminals.
*/
bool LogicGate::multipleInputs()
{
	return (gateType != NOT_GATE);
}
