// USE_SFML2

#include<SFML/Window.hpp>
#include<iostream>
#include"Game.h"


int main() {
	
	srand(time(NULL));

	// Game Creation ... Variables, Player Creation, etc
	Game startGame(1);

	// Game Start ... Updating, Drawing, and Rendering the game
	startGame.Run();
}
