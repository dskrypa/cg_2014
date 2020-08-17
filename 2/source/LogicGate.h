/**
	A logic gate.
	Extends Clickable.
	@author Douglas Skrypa
	@version 2014.03.09
*/

#ifndef LOGICGATE_H
#define LOGICGATE_H

#include <cmath>
#include <iostream>
#include "Clickable.h"
#include "Terminal.h"

#define AND_GATE	1
#define OR_GATE		2
#define NOT_GATE	3

class LogicGate: public Clickable
{
	private:
		int gateType;					//Type of gate
		Terminal out;
		Terminal in1, in2;
		void makeAndGate();				//Create an And gate
		void makeOrGate();				//Create an Or gate
		void makeNotGate();				//Create a Not gate
		void makeTerminals();			//Create appropriate terminals
	public:
		LogicGate();					//Default constructor
		LogicGate(const int, const int, const int, const int);
		Terminal* get(const int);		//Retrieve a given Terminal
		bool multipleInputs();			//True if multiple input Terminals exist
		bool equals(LogicGate*);		//True if this ID matches others' ID
};
#endif
