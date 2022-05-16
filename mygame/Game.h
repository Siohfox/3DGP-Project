#pragma once
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <stb_image.h>

// System libraries
#include <stdexcept>
#include <fstream>
#include <istream>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>  


#include "Mesh.h"
#include "Shader.h"
#include "RenderTexture.h"
#include "Movement.h"
#include "Gameobject.h"
#include "SceneObject.h"
#include "Camera.h"

class Game
{
public:
	Game();
	~Game();

	void Update();

	SDL_Window* SDLWindowInit();

	void CreateSceneObject(glm::vec3 pos, glm::vec3 orient, float angle, glm::vec3 rotAxis, const char* filePath);

	void Render(int i);


private:
   /** A method for setting up the SDL window
   * @param GameObject* otherObject a reference to the object this one is colliding with
   */
	SDL_Window* m_window;

	std::vector<SceneObject*> m_sceneObjects;
	Camera* m_cam;
	Movement* m_movement;

	Mesh* m_quad;
	Shader* m_lightShader;
	Shader* m_basicShader;
	RenderTexture* m_renderTexture;

	GLint m_modelLocation;
	GLint m_projectionLocation;

	bool m_quit;
	int m_moveCheck;
	
};


