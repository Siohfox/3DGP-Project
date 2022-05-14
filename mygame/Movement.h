#pragma once
#include <SDL2/SDL.h>
#include <iostream>

struct Movement
{
	Movement();
	~Movement();

	int Move();

private:
	int m_moveCheck;
	float m_angle;
};

