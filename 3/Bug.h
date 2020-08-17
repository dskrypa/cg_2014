/**
	Bug that exists inside a terrarium
	@author Douglas Skrypa
	@version 2014.04.09
*/

#ifndef BUG_H
#define BUG_H

#include "Animal.h"

class Bug: public Animal
{
	private:
		void initDisplay();
	public:
		Bug();
		Bug(Position);
};
#endif
