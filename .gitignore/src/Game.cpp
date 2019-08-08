#include "Game.h"

Game::Game()
{}
Game::~Game()
{}

bool Game::init()
{
	bool success = true;
	if( SDL_Init(SDL_INIT_EVERYTHING ) < 0 )
	{
		printf("SDL couldn't initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		window = SDL_CreateWindow(title,
									SDL_WINDOWPOS_CENTERED,
									SDL_WINDOWPOS_CENTERED,
									screenWidth,
									screenHeight,
									SDL_WINDOW_SHOWN);
		if( window == NULL )
		{
			printf("SDL couldn't create the window! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//loading the SDL2_iamge Library
			int imageFlags = IMG_INIT_PNG;
			if( !(IMG_Init(imageFlags) & imageFlags) )
			{
				printf( "SDL_image couldn't be initialized! SDL_image Error: %s\n", IMG_GetError() );
				quit = true;
			}
			else
			{			
				renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);
				quit = false;
				if( !loadMedia() )
				{
					printf( "Media loading error!\n");
					success = false;
					quit = true;
				}
				else
				{
					clearGameBoard();
					currentTurn = player1;
					for(int i=0; i<3; i++)
					{
						for( int j=0; j<3; j++ )
						{
							gameBoard[i][j] = empty;
						}
					}
				}	
			}
		}
	}

	return success;
}

void Game::close()
{
	//free image pointers
	SDL_DestroyTexture( graphicPlayer1 );
	graphicPlayer1 = NULL;
	SDL_DestroyTexture( graphicPlayer2 );
	graphicPlayer2 = NULL;

	//Window things
	SDL_DestroyWindow( window );
	window = NULL;
	SDL_DestroyRenderer( renderer );
	renderer = NULL;

	//Quiting out of libraries
	IMG_Quit();
	SDL_Quit();
}

void Game::clearGameBoard()
{
	for ( int i=0; i<3; i++ )
	{
		for( int j=0; j<3; j++)
		{
			gameBoard[i][j] = empty;
		}
	}
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( renderer );

	//Making lines
	SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );
	SDL_RenderDrawLine( renderer, screenWidth/3, 0, screenWidth/3, screenHeight);
	SDL_RenderDrawLine( renderer, 2*screenWidth/3, 0, 2*screenWidth/3, screenHeight);
	SDL_RenderDrawLine( renderer, 0, screenHeight/3, screenWidth, screenHeight/3);
	SDL_RenderDrawLine( renderer, 0, 2*screenHeight/3, screenWidth, 2*screenHeight/3);

	SDL_RenderPresent( renderer );

}
void Game::DrawPlayer1()
{
	//Get the mouse position
	SDL_GetMouseState( &mouse_x, &mouse_y);
	int col = mouse_x/boxWidth;
	int row = mouse_y/boxHeight;

	//Let's make a rectangle
	SDL_Rect dRect;
	dRect.x = col*boxWidth + padding;
	dRect.y = row*boxHeight + padding;
	dRect.w = boxWidth - (2 *padding );
	dRect.h = boxHeight - (2 * padding);
	SDL_RenderCopy( renderer, graphicPlayer1, NULL, &dRect);

	SDL_RenderPresent( renderer );

	//Update the game board
	gameBoard[row][col] = player1;
	
}
void Game::DrawPlayer2()
{
	SDL_GetMouseState( &mouse_x, &mouse_y );
	int col = mouse_x/boxWidth; 
	int row = mouse_y/boxHeight;

	//Let's make a rectangle
	SDL_Rect dRect;
	dRect.x = col*boxWidth + padding;
	dRect.y = row*boxHeight + padding;
	dRect.w = boxWidth - (2 *padding );
	dRect.h = boxHeight - (2 * padding);
	SDL_RenderCopy( renderer, graphicPlayer2, NULL, &dRect);

	SDL_RenderPresent( renderer );	

	//Update the game board
	gameBoard[row][col] = player2;
}

bool Game::handleEvents()
{
	SDL_Event e;
	while( SDL_PollEvent( &e ) != 0 )
	{
		switch (e.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if( currentTurn == player1 )
			{
				DrawPlayer1();
				currentTurn = player2;
				CheckScore();
			}
			else if( currentTurn == player2 )
			{
				DrawPlayer2();
				currentTurn = player1;
				CheckScore();
			}
			break;
		}
	}
}

void Game::CheckScore()
{
	for( int i=0; i<3; i++ )
	{
		if( gameBoard[0][i] + gameBoard[1][i] + gameBoard[2][i] == 3 ||
			gameBoard[i][0] + gameBoard[i][1] + gameBoard[i][2] == 3 )
		{
			SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_INFORMATION,
										"We have a winner!",
										"Player 1 has won!",
										NULL);
			clearGameBoard();
			i = 3;
		}
		else if( gameBoard[0][i] + gameBoard[1][i] + gameBoard[2][i] == 12 ||
				gameBoard[i][0] + gameBoard[i][1] + gameBoard[i][2] == 12 )
		{
			SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_INFORMATION,
										"We have a winner1",
										"Player 2 has won!",
										NULL);
			clearGameBoard();
			i = 3;
		}
	}
	if( gameBoard[0][0] + gameBoard[1][1] + gameBoard[2][2] == 3 ||
		gameBoard[0][2] + gameBoard[1][1] + gameBoard[2][0] == 3)
	{
		SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_INFORMATION, 
									"We have a winner!",
									"Player 1 has won!",
									NULL);
		clearGameBoard();
	}
	else if( gameBoard[0][0] + gameBoard[1][1] + gameBoard[2][2] == 3 ||
			gameBoard[0][2] + gameBoard[1][1] + gameBoard[2][0] == 3)
	{
		SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_INFORMATION,
									"We have a winner!",
									"Player 2 has won the game",
									NULL);
		clearGameBoard();
	}
}

void Game::printGameBoard()
{
	std::cout << "-------------------" << std::endl;
	for( int i=0; i<3; i++ )
	{
		for( int j=0; j<3; j++ )
		{
			printf("%d\t", gameBoard[i][j]);
		}
		printf("\n");
	}
	std::cout << "-------------------" << std::endl;
}

SDL_Texture* Game::loadTexture( const char* path)
{
	//Final optimized surface
	SDL_Texture *newTexture = NULL;

	//Load imgae at specified path
	SDL_Surface *loadedSurface = IMG_Load( path );
	if( loadedSurface == NULL )
	{
		printf("Unable to load %s! SDL_image Error: %s\n", path, IMG_GetError() );
	}
	else
	{
		//Create texture from the loaded surface
		newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError() );
		}

		//Free old surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}

bool Game::loadMedia()
{
	//success flag
	bool success = true;

	//Loading X image
	graphicPlayer1 = loadTexture( "..\\img\\X.png" );
	if( graphicPlayer1 == NULL )
	{
		printf( "Failed to load texture image!\n");
		success = false;
	}
	graphicPlayer2 = loadTexture( "..\\img\\O.png");
	if( graphicPlayer2 == NULL )
	{
		printf("Failed to load image!\n");
		success = false;
	}
	return success;
}
