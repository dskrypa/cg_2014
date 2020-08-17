/**
	A terminal for logic gates.
	Extends Clickable.
	@author Douglas Skrypa
	@version 2014.03.09
*/

#ifndef TERMINAL_H
#define TERMINAL_H

#include <iostream>
#include "Clickable.h"

#define TERM_OUTPUT		0
#define TERM_INPUT		1
#define TERM_INPUT1		1
#define TERM_INPUT2		2

class Terminal: public Clickable
{
	private:
		volatile bool highlighted;		//Highlighted state
		int type;						//Input/output
		void makeTerminal();			//Finalize this Terminal's glList
	public:
		Terminal();						//Default constructor
		Terminal(const int, const int, const int, const int);
		void activate();				//Sets highlighted to true
		void deactivate();				//Sets highlighted to false
		bool isActivated();				//Returns true if activated, else false
		int getType();					//Returns the input/output type
};
#endif
