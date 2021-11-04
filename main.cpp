#include <iostream>
#include "Game.h"

int main() {
	Game game;
	game.init(); //read map from files and stuff
	game.redraw(); //redraw the map
	while (game.active()) {
		game.read_input();
		game.update();
	}
}