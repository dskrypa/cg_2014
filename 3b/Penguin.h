/**
	Penguin that exists inside a terrarium
	@author Douglas Skrypa
	@version 2014.04.09
*/

#ifndef PENGUIN_H
#define PENGUIN_H

#include "Animal.h"

class Penguin: public Animal
{
	private:
		void initDisplay();
	public:
		Penguin();
		Penguin(Position);
};
#endif
