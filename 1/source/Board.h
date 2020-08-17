/**
	A Board is an object that can store multiple BoardObjects that will be
	displayed when a Board's display() method is called.
	@author Douglas Skrypa
	@version 2014.02.17
*/

#ifndef BOARD_H
#define BOARD_H

#include "BoardObject.h"
#include "Character.h"
#include <GLUT/glut.h>
#include <vector>

class Board{
	protected:
		int width, height;
		Character player;
		std::vector<BoardObject> boardObjs;
	public:
		Board(Character&, int, int);
		Character& getPlayer();
		void addItem(BoardObject&);
		int getWidth();
		int getHeight();
		void display();
		bool movePossible(BoardObject&, int);
		void attemptMove(Character&, int);
};
#endif
