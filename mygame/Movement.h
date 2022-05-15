#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <glm/glm.hpp>

class Movement
{
public:
	Movement();
	~Movement();

	bool GetQuit();
	int Update();

private:
	int m_moveCheck;
	bool m_quit;
};

