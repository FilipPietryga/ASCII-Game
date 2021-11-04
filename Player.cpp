#include "Player.h"
#include "Coord.h"
#include <memory>
#include <iostream>

Player::Player() : _coord(), _symbol('P') {

}

Player::Player(int x, int y) : _coord(x,y), _symbol('P') {

}

void Player::setCoord(int x, int y) {
	_coord.set(x, y);
}

void Player::moveRight() {
	_coord.dx(1);
}

void Player::moveLeft() {
	_coord.dx(-1);
}

void Player::moveTop() {
	_coord.dy(-1);
}

void Player::moveBottom() {
	_coord.dy(1);
}

char& Player::symbol() {
	return _symbol;
}

Coord& Player::coord() {
	return _coord;
}

void Player::print() {
	std::cout << "Player" << std::endl;
	std::cout << "X:" << _coord.x() << " Y:" << _coord.y();
}