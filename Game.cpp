#include "Game.h"
#include <fstream>
#include <iostream>
#include "WinFunc.h"
#include <conio.h>
#include <Windows.h>

#define DEBUG_PLAYER 1
#define DEBUG_COLLISION 1
#define DEBUG_ROOM 1

//should initialize everything and there should be more
//specialized Game constructors
//other way it should be treated as a singleton
//SHOULD CHECK on what to do instead of singleton
//in the projects of such, cause there will be only
//one instance of the Game object
Game::Game() : _fields(), _active(true), _input(' '), _player(), _change(false) {

}

//function initializes, or will initialize in the future,
//the room object with data read from file meaning it sets up
//fields x,y coordinates and symbols also initializing the player
// 
//maybe it should be called more generally, initialize()? 
//or load_map() ???
// 
//enable reading many maps
// 
//deduce the size of the field array from the map
//maybe specify the maxsize in the file itself?
// 
//mention the fact that there should be spaces in the maps
//and each row needs to have the same number of characters
// 
//specify the path to the file which is going to safe
//the order in which the rooms are placed
void Game::fields_init() {
	std::fstream file;
	file.open("map2.txt");
	_fields = std::shared_ptr<Field[]>(new Field[150]);
	char temp;
	int i = 0;
	int x = 0, y = 0;
	while (file >> std::noskipws >> temp) {
		if (temp == '\n') {
			y += 1;
			x = 0; 
		}
		else {
			_fields[i].scoord(x, y);
			_fields[i].dsymbol(temp);
			if (temp == 'P') {
				_player = std::shared_ptr<Player>(new Player(x, y));
			}
			x += 1;
			i += 1;
		}
	}
	room_width = x;
	room_height = y;
	file.close();
}

void Game::init() {
	fields_init();
	//split each initialization stage into different functions
	//is it even possible??
}

//maybe should be renamed so that it matches its job
//semantically?? maybe draw_init() ?? it would be only
//used once per room visit
void Game::redraw() {
	//ineffective, it should only draw the changed symbols, maybe override??
	for (int i = 0; i < 150; i++) {
		setCursorPosition(_fields[i].x(), _fields[i].y());
		std::cout << _fields[i].symbol();
	}
}

//only updates the desired field symbol
//maybe should be renamed??
//update_field() ????
void Game::redraw(int x, int y) {
	setCursorPosition(x, y);
	std::cout << _fields[y * room_width + x].symbol();
}

void Game::print() {
	for (int i = 0; i < 50; i++) {
		std::cout << _fields[i].coord().x() << " " << _fields[i].coord().y() << " ";
		//setCursorPosition(_fields[i].coord().x(), _fields[i].coord().y());
		std::cout << (int)_fields[i].symbol() << std::endl;
	}
}

//accept optinal input from keyboard
void Game::read_input() {
	while (_kbhit()) {
		_input = _getch();
	}
}

//return reference to field array, trivial
std::weak_ptr<Field[]> Game::fields() {
	return _fields;
}

//return reference to player, trivial
std::weak_ptr<Player> Game::player() {
	return _player;
}

//return the state of the game (if its active)
bool Game::active() {
	return _active;
}

//update the state of the game
void Game::update() {
#ifdef DEBUG_PLAYER
	setCursorPosition(0,20);
	_player->print();
#endif
#ifdef DEBUG_ROOM
	setCursorPosition(0, 22);
	std::cout << "WIDTH:" << room_width << " HEIGHT:" << room_height;
#endif
	check_player_change();
	delete_player_field();
	update_player();
	append_player_field();
}

void Game::check_player_change() {
	switch (_input) {
	case 'a':
	case 'A':
	case 'w':
	case 'W':
	case 's':
	case 'S':
	case 'd':
	case 'D':
		_change = true;
		break;
	default:
		_change = false;
		break;
	}
}

//process input from the console and change players state
//according to the switch-case processing mechanique
//could be put into other function so it would be
//designed better when it comes to the project management
void Game::update_player() {
	switch (_input) {
	case 'a':
	case 'A':
		if (_fields[_player->coord().y() * room_width + _player->coord().x() - 1].symbol() == ' ') {
			//read about the concept of debugging using ifdefs and other preprocessor functionalities
#ifdef DEBUG_COLLISION
			setCursorPosition(0, 24);
			std::cout << _player->coord().y() * room_width + _player->coord().x() - 1 << std::endl;
			std::cout << _fields[_player->coord().y() * room_width + _player->coord().x() - 1].symbol() << std::endl;
#endif
			_player->moveLeft();
		}
		break;
	case 'w':
	case 'W':
		if (_fields[(_player->coord().y() - 1) * room_width + _player->coord().x()].symbol() == ' ') {
#ifdef DEBUG_COLLISION
			setCursorPosition(0, 24);
			std::cout << (_player->coord().y() - 1) * room_width + _player->coord().x() << std::endl;
			std::cout << _fields[(_player->coord().y() - 1) * room_width + _player->coord().x()].symbol() << std::endl;
#endif
			_player->moveTop();
		}
		break;
	case 's':
	case 'S':
		if (_fields[(_player->coord().y() + 1) * room_width + _player->coord().x()].symbol() == ' ') {
#ifdef DEBUG_COLLISION
			setCursorPosition(0, 24);
			std::cout << (_player->coord().y() + 1) * room_width + _player->coord().x() << std::endl;
			std::cout << _fields[(_player->coord().y() + 1) * room_width + _player->coord().x()].symbol() << std::endl;
#endif
			_player->moveBottom();
		}
		break;
	case 'd':
	case 'D':
		if (_fields[_player->coord().y() * room_width + _player->coord().x() + 1].symbol() == ' ') {
#ifdef DEBUG_COLLISION
			setCursorPosition(0, 24);
			std::cout << _player->coord().y() * room_width + _player->coord().x() + 1 << std::endl;
			std::cout << _fields[_player->coord().y() * room_width + _player->coord().x() + 1].symbol() << std::endl;
#endif
			_player->moveRight();
		}
		break;
	default:
		break;
	}
	_input = ' ';
}

//remove the player from the previous position on the map
void Game::delete_player_field() {
	//ineffective, should only change the players field
	if (_change) {
		_fields[room_width * _player->coord().y() + _player->coord().x()].dsymbol(' ');
		redraw(_player->coord().x(), _player->coord().y());
	}
}

//put player in the new position on the map
void Game::append_player_field() {
	if (_change) {
		_fields[room_width * _player->coord().y() + _player->coord().x()].dsymbol('P');
		redraw(_player->coord().x(), _player->coord().y());
		ShowConsoleCursor(false);
	}
}


//trivial
void Game::print_instructions() {
	//implement reading instructions from files and displaying it in the console, below the room
	//relatively to the screen
	//it might be on all the time
	//it might be only while the player specifies for it to be (like no a button)
	//or make it a switchable option in the menu like display instructions
	//or like verbose mode
	std::cout << "\" \" (air) - free space, you can move thorough" << std::endl;
	std::cout << "# - unmovable object" << std::endl;
}