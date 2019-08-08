#include "Game.h"

int main(int argc, char* argv[])
{
	
	Game *game;
	game = new Game();

	game->init();
	game->clearGameBoard();
	
	while( !game->quit)
	{
		game->handleEvents();
		
	}

	game->close();

	return 0;
}
