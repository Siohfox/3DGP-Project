// Tell system that SDL and STB IMAGE is already handled
#define SDL_MAIN_HANDLED

#include "Game.h"

int main()
{
	std::unique_ptr<Game> game = std::make_unique<Game>();

	game->Update();

	return 0;
}