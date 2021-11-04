#include "Coord.h"

Coord::Coord() : _x(-1), _y(-1) {

}

Coord::Coord(int x, int y) : _x(x), _y(y) {

}

int Coord::x() {
	return this->_x;
}

int Coord::y() {
	return this->_y;
}

void Coord::dx(int dx) {
	_x += dx;
}

void Coord::dy(int dy) {
	_y += dy;
}

void Coord::set(int x, int y) {
	this->_x = x;
	this->_y = y;
}