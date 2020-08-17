/**
	A Board is an object that can store multiple BoardObjects that will be
	displayed when a Board's display() method is called.
	@author Douglas Skrypa
	@version 2014.02.17
*/

#include "Board.h"
#include "BoardObject.h"
#include "Character.h"
#include <GLUT/glut.h>
#include <vector>

/**
	Constructs a Board.
	@param player a Character that will interact with items on this Board
	@param width the width in pixels
	@param height the height in pixels
*/
Board::Board(Character& player, int width, int height)
{
	this->player = player;
	this->width = width;
	this->height = height;
}

/**
	Returns a reference to the Character that is on this Board.
	@return A reference to the stored Character player
*/
Character& Board::getPlayer()
{
	return player;
}

/**
	Adds a reference to a BoardObject that should be drawn on this Board.
	@param bObj a BoardObject to appear on this Board
*/
void Board::addItem(BoardObject& bObj)
{
	boardObjs.push_back(bObj);
}

/**
	Returns the width of this Board
	@return This Board's width
*/
int Board::getWidth()
{
	return width;
}

/**
	Returns the height of this Board
	@return This Board's height
*/
int Board::getHeight()
{
	return height;
}

/**
	Draws all BoardObjects that occupy this Board.
*/
void Board::display()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	for(int x = 0; (unsigned)x < boardObjs.size(); x++){
		boardObjs[x].display();
	}
	player.display();

	glFlush();
	glutSwapBuffers();
}

/**
	Determines whether it is possible for a BoardObject to move in a given
	direction.
	@param bObj a BoardObject that is attempting to move
	@param dir the direction that bObj is traveling
	@return true if nothing is obstructing bObj's path, otherwise false
*/
bool Board::movePossible(BoardObject& bObj, int dir)
{
	/**
		Test each BoardObject on this Board to see if the given BoardObject will
		collide with it while moving in the given direction.
	*/
	for(int x = 0; (unsigned)x < boardObjs.size(); x++){
		/**
			Since BoardObject's willCollideWith() method is based on testing a
			BoardObject's corners, it was failing when the stationary object was
			smaller than the moving one. Both corners of the moving one would be
			outside the bounds of the smaller one, which allowed it to overlap.
			In order to keep the willCollideWith() method simple, this problem
			was fixed by adding the inverse check here.
			
			To facilitate this step, the ints used to represent a given
			direction were set to be +/- 1 for movement along the y axis, and
			+/- 2 for movement along the x axis, to make flipping the direction
			easier. Due to inexperience with c/c++, I could not figure out how
			to make these static constants that were accessable from other
			classes.  I suspect the solution may be in namespaces.
		*/
		if(bObj.willCollideWith(boardObjs[x], dir) || boardObjs[x].willCollideWith(bObj, dir*-1)){
			return false;
		}
	}
	return true;	//All BoardObjects checked; no collisions detected
}

/**
	Moves the given Character as many spaces as possible in the given direction.
	@param p a Character that is attempting to move
	@param dir the direction that p is traveling
*/
void Board::attemptMove(Character& p, int dir)
{
	/**
		The number of pixels that a Character advances in a single round is
		equal to its speed. Obstacles may prevent it from moving the full
		distance determined by its speed, but it should be able to move as far
		as it can before stopping.  To accomplish this, movement by a single
		pixel is attempted [Character's speed] times.
	*/
	for(int x = 0; x < p.getSpeed(); x++){
		if(movePossible(p, dir)){
			switch(dir){
				case 1:		p.addY(1);	break;	//Up
				case -1:	p.addY(-1);	break;	//Down
				case 2:		p.addX(-1);	break;	//Left
				case -2:	p.addX(1);	break;	//Right
			}
			glutPostRedisplay();
		} else {
			/**
				If it can't move in the given direction, don't waste cpu cycles
				on checking whether it can move after it was already unable to.
			*/
			break;
		}
	}
}
