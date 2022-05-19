#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <glm/glm.hpp>

class Movement
{
public:
	/** A constructor for Movement
	*/
	Movement();

	/** A destructor for Movement
	*/
	~Movement();

	/** A method to return if the program has quit or not
	*/
	bool GetQuit();

	/** A method to update the movement
	* @return an integer value specifying which direction to move in
	*/
	int Update();

private:
	/** A movement check integer to specify direction of movement
	*/
	int m_moveCheck;

	/** A quit variable to exit the main game loop
	*/
	bool m_quit;
};

