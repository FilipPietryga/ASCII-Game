#pragma once
#include "Field.h"
#include <memory>
class Player
{
private:
	Coord _coord;
	char _symbol;
public:
	Player();
	Player(int x, int y);
	void setCoord(int x, int y);
	void moveRight();
	void moveLeft();
	void moveTop();
	void moveBottom();
	char& symbol();
	Coord& coord();
	void print();
	//move player related tasks to the Player class
};