#include "Game.h"
// Graphics libraries

Game::Game()
{
	m_window = SDLWindowInit();
	m_cam = new Camera();
	m_movement = new Movement();


	m_lightShader = new Shader("resources/vertex.txt", "resources/fragmentShader.txt");
	m_basicShader = new Shader("resources/basicVertexShader.txt", "resources/basicFragmentShader.txt");
	m_quad = new Mesh();
	m_renderTexture = new RenderTexture(1024,1024);

	m_modelLocation = glGetUniformLocation(m_lightShader->id(), "u_Model");
	m_projectionLocation = glGetUniformLocation(m_lightShader->id(), "u_Projection");

	m_quit = false;
	m_moveCheck = 0;

	CreateSceneObject(glm::vec3(0.0f, 0.0f, -20.0f), glm::vec3(0.0f), 90, glm::vec3(0, 1, 0), "models/curuthers/curuthers.obj");
	CreateSceneObject(glm::vec3(5.0f, 0.0f, -20.0f), glm::vec3(0.0f), 90, glm::vec3(0, 1, 0), "models/curuthers/curuthers.obj");

}

Game::~Game()
{
	SDL_DestroyWindow(m_window);
}


SDL_Window* Game::SDLWindowInit()
{
	int w = 800, h = 600;
	SDL_Window* window = SDL_CreateWindow("OpenGL Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (!SDL_GL_CreateContext(window))
	{
		throw std::runtime_error("Failed to create OpenGL context");
	}

	// Initialise glew and check for errors
	if (glewInit() != GLEW_OK)
	{
		throw std::runtime_error("Failed to create OpenGL context");
	}
	return window;
}

void Game::CreateSceneObject(glm::vec3 pos, glm::vec3 orient, float angle, glm::vec3 rotAxis, const char* filePath)
{
	SceneObject* newObj = new SceneObject(pos, orient, angle, rotAxis, filePath);

	m_sceneObjects.push_back(newObj);
}

void Game::Render(int i)
{
	// 1 | Start binding to render texture
	glViewport(0, 0, 1024, 1024);
	m_renderTexture->bind();
	// 2 | Clear black
	if (i < 1)
	{
		glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	
	// Instruct OpenGL to use our shader program and our VAO
	glUseProgram(m_lightShader->id());
	glBindVertexArray(m_quad->getid());
	glBindTexture(GL_TEXTURE_2D, m_sceneObjects.at(i)->GetModelTextureID());

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Upload the model matrix
	glUniformMatrix4fv(m_modelLocation, 1, GL_FALSE, glm::value_ptr(m_sceneObjects.at(i)->GetIdentity()));
	// Upload the projection matrix
	glUniformMatrix4fv(m_projectionLocation, 1, GL_FALSE, glm::value_ptr(m_cam->GetProjection()));
	glBindVertexArray(m_sceneObjects.at(i)->GetModelVaoID());
	glDrawArrays(GL_TRIANGLES, 0, m_sceneObjects.at(i)->GetModelVertexCount());
	// Reset the state
	glBindVertexArray(0);
	glUseProgram(0);
	glViewport(0, 0, 800, 600);
	m_renderTexture->unbind();
	// Draw tringl
	glClearColor(0, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(m_basicShader->id());
	glBindVertexArray(m_quad->getid());
	glBindTexture(GL_TEXTURE_2D, m_renderTexture->getTexture());
	glDrawArrays(GL_TRIANGLES, 0, m_quad->vert_count());
}


void Game::Update()
{
	while (!m_quit)
	{
		m_quit = m_movement->GetQuit();
		m_moveCheck = m_movement->Update();

		switch (m_moveCheck)
		{
		case 1:
			m_sceneObjects.at(0)->TranslateObject(glm::vec3(0.0f, 0.0f,- 0.5f));
			m_cam->TranslateObject(glm::vec3(0.0f, 0.0f, -0.5f));
			//angle = 1.0f;
			break;
		case 2:
			m_sceneObjects.at(0)->TranslateObject(glm::vec3(0.0f, 0.0f, 0.5f));
			//angle = -1.0f;
			break;
		case 3:
			m_sceneObjects.at(0)->TranslateObject(glm::vec3(0.0f, 0.0f, 0.5f));
			//cam->TranslateObject(glm::vec3(0.0f, 0.0f, 0.5f));
			break;
		case 4:
			m_sceneObjects.at(0)->TranslateObject(glm::vec3(0.0f, 0.0f, -0.5f));
			//cam->TranslateObject(glm::vec3(0.0f, 0.0f, -0.5f));
			break;
		default:
			break;
		}


		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);

		for (size_t i = 0; i < m_sceneObjects.size(); i++)
		{
			Render(i);
		}

		glDisable(GL_BLEND);
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);

		SDL_GL_SwapWindow(m_window);
	}
	
}