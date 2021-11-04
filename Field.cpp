#include "Field.h"

Field::Field() : _coord(), _symbol(' ') {
	
}

Coord Field::coord() {
	return _coord;
}

void Field::scoord(int x, int y) {
	_coord.set(x, y);
}

char& Field::symbol() {
	return _symbol;
}

void Field::dsymbol(char symbol) {
	_symbol = symbol;
}

int Field::x() {
	return _coord.x();
}

int Field::y() {
	return _coord.y();
}