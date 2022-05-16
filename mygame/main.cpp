// Tell system that SDL and STB IMAGE is already handled
#define SDL_MAIN_HANDLED
//#define STB_IMAGE_IMPLEMENTATION

// Graphics libraries
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <stb_image.h>
//#include <wavefront/wavefront.h>

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

SDL_Window* renderWindow() 
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


int main()
{
	// Render the window using SDL
	SDL_Window* window = renderWindow();

	Mesh quad(0);
	Shader ls("resources/vertex.txt", "resources/fragmentShader.txt");
	Shader bs("resources/basicVertexShader.txt", "resources/basicFragmentShader.txt");

	Camera* cam = new Camera();

	//glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)600 / (float)600, 0.1f, 100.f);
	GLint modelLoc = glGetUniformLocation(ls.id(), "u_Model");
	GLint projectionLoc = glGetUniformLocation(ls.id(), "u_Projection");

	float angle = 0;
	int width = 0;
	int height = 0;

	SDL_GetWindowSize(window, &width, &height);


	// Define width and height
	int w = 0;
	int h = 0;

	//unsigned char* data = stbi_load("image.png", &w, &h, NULL, 4);

	//if (!data)
	//{
	//	std::cout << "ERROR: No image data found" << std::endl;
	//	throw std::exception("No image data");
	//}

	SceneObject* curuthers = new SceneObject(glm::vec3(0.0f, 0.0f, -20.0f), glm::vec3(0.0f), 180, glm::vec3(0, 1, 0), "models/curuthers/curuthers.obj");
	//SceneObject* sphere = new SceneObject(glm::vec3(0.0f, 0.0f, -20.0f), glm::vec3(0.0f), 0, glm::vec3(0, 1, 0), "models/sphere/sphere.obj");

	// MAIN LOOP

	RenderTexture rt(1024, 1024);

	bool quit = false;
	int moveCheck = 0;


	Movement* movement = new Movement();
	// Prepare the perspective projection matrix

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);  
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);


	while (!quit)
	{

		quit = movement->GetQuit();
		moveCheck = movement->Update();

		switch (moveCheck)
		{
		case 1:
			curuthers->RotateObject(angle, glm::vec3(0.0f, 1.0f, 0.0f));
			angle = 1.0f;
			break;
		case 2:
			curuthers->RotateObject(angle, glm::vec3(0.0f, 1.0f, 0.0f));
			angle = -1.0f;
			break;
		case 3:
			curuthers->TranslateObject(glm::vec3(0.0f, 0.0f, 0.5f));
			cam->TranslateObject(glm::vec3(0.0f, 0.0f, 0.5f));
			break;
		case 4:
			curuthers->TranslateObject(glm::vec3(0.0f, 0.0f, -0.5f));
			cam->TranslateObject(glm::vec3(0.0f, 0.0f, -0.5f));
			break;
		default:
			break;
		}

		// 1 | Start binding to render texture
		glViewport(0, 0, 1024, 1024);
		rt.bind();
		// 2 | Clear black
		glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Instruct OpenGL to use our shader program and our VAO
		glUseProgram(ls.id());
		glBindVertexArray(quad.getid());
		glBindTexture(GL_TEXTURE_2D, curuthers->GetModelTextureID());
		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		// Upload the model matrix
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(curuthers->GetIdentity()));
		// Upload the projection matrix
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(cam->GetProjection()));
		glBindVertexArray(curuthers->GetModelVaoID());
		glDrawArrays(GL_TRIANGLES, 0, curuthers->GetModelVertexCount());
		// Reset the state
		glBindVertexArray(0);
		glUseProgram(0);
		glViewport(0, 0, 800, 600);
		rt.unbind();
		// Draw tringl
		glClearColor(0, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(bs.id());
		glBindVertexArray(quad.getid());
		glBindTexture(GL_TEXTURE_2D, rt.getTexture());
		glDrawArrays(GL_TRIANGLES, 0, quad.vert_count());

		// Finish drawing cat


		//// 1 | Start binding to render texture
		//glViewport(0, 0, 1024, 1024);
		//rt.bind();
		//// 2 | Clear black
		//glClearColor(1, 1, 1, 1);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//// Instruct OpenGL to use our shader program and our VAO
		//glUseProgram(ls.id());
		//glBindVertexArray(quad.getid());
		//glBindTexture(GL_TEXTURE_2D, sphere->GetModelTextureID());
		//glEnable(GL_CULL_FACE);
		//glEnable(GL_BLEND);
		//glEnable(GL_DEPTH_TEST);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//// Upload the model matrix
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(sphere->GetIdentity()));
		//// Upload the projection matrix
		//glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(cam->GetProjection()));
		//glBindVertexArray(sphere->GetModelVaoID());
		//glDrawArrays(GL_TRIANGLES, 0, sphere->GetModelVertexCount());
		//// Reset the state
		//glBindVertexArray(0);
		//glUseProgram(0);
		//glViewport(0, 0, 800, 600);
		//rt.unbind();
		//// Draw tringl
		//glClearColor(0, 1, 1, 1);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glUseProgram(bs.id());
		//glBindVertexArray(quad.getid());
		//glBindTexture(GL_TEXTURE_2D, rt.getTexture());
		//glDrawArrays(GL_TRIANGLES, 0, quad.vert_count());


		glDisable(GL_BLEND);
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		// This function just updates the window
		SDL_GL_SwapWindow(window);
	}
	return 0;
}