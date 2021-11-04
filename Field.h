#pragma once
#include "Coord.h"

class Field
{
private:
	Coord _coord;
	char _symbol;
	//todo: color settings
public:
	Field();
	Coord coord();
	char& symbol(); //get
	void dsymbol(char symbol); //set 
	void scoord(int x, int y);
	int x();
	int y();
};