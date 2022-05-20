#include "Movement.h"

Movement::Movement()
{
	m_moveCheck = 0;
	m_quit = false;
}

Movement::~Movement()
{

}

bool Movement::GetQuit()
{
	return m_quit;
}


int Movement::Update()
{
	SDL_Event event = { 0 };

	while (SDL_PollEvent(&event))
	{

		switch (event.type)
		{
		case SDL_KEYDOWN:
			//std::cout << "Key Down" << std::endl;
			switch (event.key.keysym.sym)
			{
			case SDLK_a:
				m_moveCheck = 1;
				break;
			case SDLK_d:
				m_moveCheck = 2;
				break;
			case SDLK_w:
				m_moveCheck = 3;
				break;
			case SDLK_s:
				m_moveCheck = 4;
				break;
			case SDLK_ESCAPE:
				m_quit = true;
				break;
			}
			break;
		case SDL_KEYUP:
			//std::cout << "Key Up" << std::endl;
			switch (event.key.keysym.sym)
			{
			case SDLK_a:
				m_moveCheck = 0;
				break;
			case SDLK_d:
				m_moveCheck = 0;
				break;
			case SDLK_w:
				m_moveCheck = 0;
				break;
			case SDLK_s:
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