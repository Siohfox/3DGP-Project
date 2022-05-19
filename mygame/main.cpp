// Tell system that SDL and STB IMAGE is already handled
#define SDL_MAIN_HANDLED

#include "Game.h"

int main()
{
	// Create instance of a game
	std::unique_ptr<Game> game = std::make_unique<Game>();

	// Go through game update -- quit back here when game is over
	game->Update();

	return 0;
}