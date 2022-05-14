// Tell system that SDL and STB IMAGE is already handled
#define SDL_MAIN_HANDLED
//#define STB_IMAGE_IMPLEMENTATION

// Graphics libraries
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <stb_image.h>
#include <wavefront/wavefront.h>

// System libraries
#include <stdexcept>
#include <fstream>
#include <istream>
#include <iostream>
#include <string>
#include <vector>


#include "Mesh.h"
#include "Shader.h"
#include "RenderTexture.h"
#include "Movement.h"

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

	GLint modelLoc = glGetUniformLocation(ls.id(), "u_Model");
	GLint projectionLoc = glGetUniformLocation(ls.id(), "u_Projection");

	float angle = 0;
	int width = 0;
	int height = 0;

	SDL_GetWindowSize(window, &width, &height);

	

		/*
			Loading system data
		*/

	// Define width and height
	int w = 0;
	int h = 0;

	unsigned char* data = stbi_load("image.png", &w, &h, NULL, 4);

	if (!data)
	{
		std::cout << "ERROR: No image data found" << std::endl;
		throw std::exception("No image data");
	}



	WfModel curuthers = { 0 };

	if (WfModelLoad("models/curuthers/curuthers.obj", &curuthers) != 0)
	{
		throw std::runtime_error("failed to load model thingy");
	}


	// MAIN LOOP

	RenderTexture rt(1024, 1024);

	bool quit = false;
	int moveCheck = 0;
	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(0, 0, -20.5f));


	Movement* movement = new Movement();

	while (!quit)
	{
		SDL_Event event;
		if (event.type = quit)
		{
			quit = true;
		}

		moveCheck = movement->Move();

		// 1 | Start binding to render texture
		glViewport(0, 0, 1024, 1024);
		rt.bind();

		// 2 | Clear black
		glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Prepare the perspective projection matrix
		glm::mat4 projection = glm::perspective(glm::radians(45.0f),
			(float)600 / (float)600, 0.1f, 100.f);

		// Prepare the model matrix


		switch (moveCheck)
		{
		case 1:
			model = glm::rotate(model, glm::radians(angle), glm::vec3(0, 1, 0));
			angle = 1.0f;
			break;
		case 2:
			model = glm::rotate(model, glm::radians(angle), glm::vec3(0, 1, 0));
			angle = -1.0f;
			break;
		case 3:
			model += glm::translate(model, glm::vec3(0, 0, 0.5f));
			break;
		case 4:
			model += glm::translate(model, glm::vec3(0, 0, -0.5f));
			break;
		default:
			break;
		}

		// Increase the float angle so next frame the triangle rotates further

		// Make sure the current program is bound
#
		// Instruct OpenGL to use our shader program and our VAO
		glUseProgram(ls.id());
		glBindVertexArray(quad.getid());
		glBindTexture(GL_TEXTURE_2D, curuthers.textureId);
		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Upload the model matrix
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		// Upload the projection matrix
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE,
		glm::value_ptr(projection));


		glBindVertexArray(curuthers.vaoId);
		glDrawArrays(GL_TRIANGLES, 0, curuthers.vertexCount);


		glDisable(GL_BLEND);
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);

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

		
		

		// This function just updates the window
		SDL_GL_SwapWindow(window);
	}
	return 0;
}