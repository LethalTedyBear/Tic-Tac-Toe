#pragma once

#include <SDL.h>
#include "SDL_image.h"
#include <iostream>

class Game
{
public:
	Game();
	~Game();

	//Starts SDL and makes window
	bool init();
	//Closes SDL
	void close();

	//Creates Game Board
	//And rendering objects
	void clearGameBoard();
	void DrawPlayer1();
	void DrawPlayer2();
	void printGameBoard();

	//Handling events
	bool handleEvents();
	void CheckScore();

	//Loading the graphics
	SDL_Texture *loadTexture( const char* path );
	bool loadMedia();

	

	bool quit;
private:
	//Screen Dimensions
	const int screenWidth = 640;
	const int screenHeight = 480;
	const char *title = "My first game!";

	//Box Dimensions
	const int boxWidth = screenWidth / 3;
	const int boxHeight = screenHeight / 3;
	const int padding = 10;
	
	//Tracking the position of the mouse
	int mouse_x, mouse_y;
	
	//Tracking the state of the board
	int gameBoard[3][3];
	enum tileState {
		empty = 0,
		player1,
		player2=4
	};

	//Player turn
	int currentTurn;

	//Pointers
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	SDL_Texture *graphicPlayer1;
	SDL_Texture *graphicPlayer2;
};