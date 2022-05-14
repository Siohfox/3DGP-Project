#include "Movement.h"

Movement::Movement()
{
	m_moveCheck = 0;
	m_angle = 0;
}


int Movement::Move()
{
	SDL_Event event = { 0 };

	while (SDL_PollEvent(&event))
	{
		std::cout << "potato";
		switch (event.type)
		{
		case SDL_KEYDOWN:
			//std::cout << "Key Down" << std::endl;
			switch (event.key.keysym.sym)
			{
			case SDLK_a:
				std::cout << "Left key pressed" << std::endl;
				m_moveCheck = 1;
				break;
			case SDLK_d:
				std::cout << "Right key pressed" << std::endl;
				m_moveCheck = 2;
				break;
			case SDLK_w:
				std::cout << "Up key pressed" << std::endl;
				m_moveCheck = 3;
				break;
			case SDLK_s:
				std::cout << "Down key pressed" << std::endl;
				m_moveCheck = 4;
				break;
			}
			break;
		case SDL_KEYUP:
			//std::cout << "Key Up" << std::endl;
			switch (event.key.keysym.sym)
			{
			case SDLK_a:
				std::cout << "Left key released" << std::endl;
				m_moveCheck = 0;
				m_angle = 0;
				break;
			case SDLK_d:
				std::cout << "Right key released" << std::endl;
				m_moveCheck = 0;
				m_angle = 0;
				break;
			case SDLK_w:
				std::cout << "Up key released" << std::endl;
				m_moveCheck = 0;
				break;
			case SDLK_s:
				std::cout << "Down key released" << std::endl;
				m_moveCheck = 0;
				break;
			}
			break;
		default:
			break;
		}
	}
	

	return m_moveCheck;
}