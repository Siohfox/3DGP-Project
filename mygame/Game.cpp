#include "Game.h"
#include "Enemy.h"
#include "Mesh.h"
#include "Shader.h"
#include "RenderTexture.h"
#include "Movement.h"
#include "Gameobject.h"
#include "SceneObject.h"
#include "Camera.h"
#include "glm/gtx/string_cast.hpp"
// Graphics libraries

Game::Game()
{
	m_window = SDLWindowInit();
	m_cam = new Camera(glm::vec3(0.0f, -10.0f, -7.0f), glm::vec3(10.0f, 0.0f, 0.0f), 40.0f, glm::vec3 (1, 0, 0));
	m_movement = new Movement();


	m_lightShader = new Shader("resources/vertex.txt", "resources/fragmentShader.txt");
	m_basicShader = new Shader("resources/basicVertexShader.txt", "resources/basicFragmentShader.txt");
	m_quad = new Mesh();
	m_renderTexture = new RenderTexture(1024,1024);

	m_modelLocation = glGetUniformLocation(m_lightShader->id(), "u_Model");
	m_projectionLocation = glGetUniformLocation(m_lightShader->id(), "u_Projection");

	m_quit = false;
	m_moveCheck = 0;
	m_randGen = false;

	CreateSceneObject(glm::vec3(0.0f, 0.0f, -20.0f), glm::vec3 (1.0f,1.0f,1.0f), glm::vec3(0.0f), 90, glm::vec3(0, 1, 0), "models/curuthers/curuthers.obj", GameObject::ObjectType::Player);
	//CreateSceneObject(glm::vec3(5.0f, 0.0f, -20.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f), 90, glm::vec3(0, 1, 0), "models/curuthers/curuthers.obj", GameObject::ObjectType::Other);

	CreateSceneObject(glm::vec3(-20.0f, -2.5f, -20.0f), glm::vec3(2.0f, 1.0f, 1.0f), glm::vec3(0.0f), 90, glm::vec3(0, 1, 0), "models/floor/woodfloor.obj", GameObject::ObjectType::Floor);
	CreateSceneObject(glm::vec3(-10.0f, -2.5f, -20.0f), glm::vec3(2.0f, 1.0f, 1.0f), glm::vec3(0.0f), 90, glm::vec3(0, 1, 0), "models/floor/woodfloor.obj", GameObject::ObjectType::Floor);
	CreateSceneObject(glm::vec3(0.0f , -2.5f, -20.0f), glm::vec3(2.0f, 1.0f, 1.0f), glm::vec3(0.0f), 90, glm::vec3(0, 1, 0), "models/floor/woodfloor.obj", GameObject::ObjectType::Floor);
	CreateSceneObject(glm::vec3(10.0f, -2.5f, -20.0f), glm::vec3(2.0f, 1.0f, 1.0f), glm::vec3(0.0f), 90, glm::vec3(0, 1, 0), "models/floor/woodfloor.obj", GameObject::ObjectType::Floor);

	CreateSceneObject(glm::vec3(20.0f, 0.0f, -24.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f), 90, glm::vec3(0, 1, 0), "models/sphere/sphere.obj", GameObject::ObjectType::Enemy);
	CreateSceneObject(glm::vec3(25.0f, 0.0f, -20.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f), 90, glm::vec3(0, 1, 0), "models/sphere/sphere.obj", GameObject::ObjectType::Enemy);
	CreateSceneObject(glm::vec3(30.0f, 0.0f, -16.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f), 90, glm::vec3(0, 1, 0), "models/sphere/sphere.obj", GameObject::ObjectType::Enemy);
	CreateSceneObject(glm::vec3(35.0f, 0.0f, -24.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f), 90, glm::vec3(0, 1, 0), "models/sphere/sphere.obj", GameObject::ObjectType::Enemy);
	CreateSceneObject(glm::vec3(40.0f, 0.0f, -20.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f), 90, glm::vec3(0, 1, 0), "models/sphere/sphere.obj", GameObject::ObjectType::Enemy);
	CreateSceneObject(glm::vec3(45.0f, 0.0f, -16.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f), 90, glm::vec3(0, 1, 0), "models/sphere/sphere.obj", GameObject::ObjectType::Enemy);

	m_sceneObjects.at(5)->SetPos(glm::vec3(4.0f, 0.0f, -24.0f));
	m_sceneObjects.at(5)->SetPos(glm::vec3(0.0f, 0.0f, -24.0f));
	m_sceneObjects.at(5)->SetPos(glm::vec3(-4.0f, 0.0f, -24.0f));
	m_sceneObjects.at(5)->SetPos(glm::vec3(4.0f, 0.0f, -24.0f));
	m_sceneObjects.at(5)->SetPos(glm::vec3(0.0f, 0.0f, -24.0f));
	m_sceneObjects.at(5)->SetPos(glm::vec3(4.0f, 0.0f, -24.0f));
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

void Game::CreateSceneObject(glm::vec3 pos, glm::vec3 scale, glm::vec3 orient, float angle, glm::vec3 rotAxis, const char* filePath, GameObject::ObjectType type)
{
	SceneObject* newObj = new SceneObject(pos, scale, orient, angle, rotAxis, filePath, type);

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
		if (!m_randGen)
		{
			m_randGen = true;
			srand(time(NULL));
		}

		m_quit = m_movement->GetQuit();
		m_moveCheck = m_movement->Update();
		

		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);

		for (size_t i = 0; i < m_sceneObjects.size(); i++)
		{
			switch (m_sceneObjects.at(i)->GetObjectType())
			{
				case GameObject::ObjectType::Player:
				{
					switch (m_moveCheck)
					{
						case 1:
							if(m_sceneObjects.at(i)->GetPos().z > -30.0f) { m_sceneObjects.at(i)->TranslateObject(glm::vec3(0.0f, 0.0f, -0.3f)); }
							break;
						case 2:
							if (m_sceneObjects.at(i)->GetPos().z < -12.0f) { m_sceneObjects.at(i)->TranslateObject(glm::vec3(0.0f, 0.0f, 0.3f)); }
							break;
						case 3:

							if (m_sceneObjects.at(i)->GetPos().x < 8.0f) { m_sceneObjects.at(i)->TranslateObject(glm::vec3(0.3f, 0.0f, 0.0f)); }
							break;
						case 4:
							
							if (m_sceneObjects.at(i)->GetPos().x > -9.0f) { m_sceneObjects.at(i)->TranslateObject(glm::vec3(-0.3f, 0.0f, 0.0f)); }
							break;
						default:
							break;
					}
					break;
				}
				case GameObject::ObjectType::Enemy:
				{
					m_sceneObjects.at(i)->TranslateObject(glm::vec3(0.0f, 0.0f, -0.1f));

					for (size_t i = 0; i < 6; i++)
					{
						if (m_sceneObjects.at(i + 5)->GetPos().z <= -70.0f - (i * 5))
						{
							m_sceneObjects.at(i + 5)->TranslateObject(glm::vec3(0.0f, 0.0f, 50.0f * (rand() % 2 + 1)));
						}


						if ((m_sceneObjects.at(0)->GetPos().z - (23.5f + i + 5.0f)) < (m_sceneObjects.at(i + 5)->GetPos().z + 1.5f) && (m_sceneObjects.at(0)->GetPos().z) - (23.5f + i + 5.0f) > (m_sceneObjects.at(i + 5)->GetPos().z - 1.5f))
						{
							if ((m_sceneObjects.at(0)->GetPos().x < (m_sceneObjects.at(i + 5)->GetPos().x + 2.0f) && (m_sceneObjects.at(0)->GetPos().x) >(m_sceneObjects.at(i + 5)->GetPos().x - 2.0f)))
							{
								std::cout << "collision with sphere " << i << " at " << glm::to_string(m_sceneObjects.at(i + 5)->GetPos()) << std::endl;
							}
						}
					}
					break;
				}

				case GameObject::ObjectType::Floor:
				{
					m_sceneObjects.at(i)->TranslateObject(glm::vec3(0.0f, 0.0f, -0.1f));

					for (size_t i = 0; i < 4; i++)
					{
						if (m_sceneObjects.at(i + 1)->GetPos().z <= (-20.0f) - (i * (10 )))
						{
							m_sceneObjects.at(i + 1)->TranslateObject(glm::vec3(0.0f, 0.0f, (40.0f)));
						}
					}
					break;
				}
				default:
					break;
			}


			Render(i);
		}

		glDisable(GL_BLEND);
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);

		SDL_GL_SwapWindow(m_window);
	}
	
}