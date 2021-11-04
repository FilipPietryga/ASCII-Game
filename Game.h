#pragma once
#include "Field.h"
#include <memory>
#include "Player.h"
#include <iostream>
class Game
{
private:
	std::shared_ptr<Field[]> _fields;
	void fields_init(); //view
	std::shared_ptr<Player> _player;
	bool _active; //model
	char _input; //model
	bool _change; //model
	std::string _instructions; //instructions for the game
	//read on how to do menus in cpp cmd the best way
public:
	Game();
	void init();
	std::weak_ptr<Field[]> fields();
	std::weak_ptr<Player> player();
	//hold file refenrence? no...
	void print(); //move to the view
	void display(); //move to the view
	void read_input(); //move to the controller
	bool active(); //move to the model
	void redraw(); //move to the view
	void redraw(int, int); //move to the view
	void update(); //view
	void update_player(); //model, player??
	void update_fields(); //model, room object??
	void delete_player_field(); //model, room object
	void append_player_field(); //model, room object
	void check_player_change();
	int room_width; //make private and start with _ then move to the model
	int room_height; // same as ^
	void print_instructions(); //move to the view
	void load_instructions(); //read instructions data from files
	//try to implement to MVC model in this project
	//display data in the view
};

//how to i store information about the player??
//in the player class and then move the object through the objects
//or
//do i have it in the model and put information from there
//to more generic functions in the room model
//id rather pick the second one but ive got to think