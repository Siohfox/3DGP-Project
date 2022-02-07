// Tell system that SDL is already handled
#define SDL_MAIN_HANDLED

// Graphics libraries
#include "SDL2/SDL.h"
#include "GL/glew.h"

// System libraries
#include <stdexcept>
#include <fstream>
#include <istream>
#include <iostream>
#include <string>

// Github Test

// Input file to return it as a string
std::string getFileCode(std::string fileName)
{
	std::string line;
	std::string fileContent;
	std::ifstream myfile(fileName);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			std::cout << line << '\n';

			fileContent += line;
		}

		myfile.close();
	}
	return fileContent;
}

int main()
{

	// ======================================= WINDOW RENDER STUFF ======================================

	SDL_Window* window = SDL_CreateWindow("OpenGL Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (!SDL_GL_CreateContext(window))
	{
		throw std::runtime_error("Failed to create OpenGL context");
	}

	// Initialise glew and check for errors
	if (glewInit() != GLEW_OK)
	{
		throw std::runtime_error("Failed to create OpenGL context");
	}

	// ======================================= Preparing the Primitive Shape Data ======================================
	const GLfloat positions[] = {
	  0.0f, 0.5f, 0.0f,
	  -0.5f, -0.5f, 0.0f,
	  0.5f, -0.5f, 0.0f
	};

	const GLfloat colours[] = {
	  1.0f, 0.0f, 0.0f, 1.0f,
	  0.0f, 1.0f, 0.0f, 1.0f,
	  0.0f, 0.0f, 1.0f, 1.0f,
	};

	GLuint positionsVboId = 0;

	// Create a new VBO on the GPU and bind it
	glGenBuffers(1, &positionsVboId);

	if (!positionsVboId)
	{
		throw std::exception();
	}

	glBindBuffer(GL_ARRAY_BUFFER, positionsVboId);

	// Upload a copy of the data from memory into the new VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	// Reset the state
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint vaoId = 0;

	// Create a new VAO on the GPU and bind it
	glGenVertexArrays(1, &vaoId);

	if (!vaoId)
	{
		throw std::exception();
	}

	glBindVertexArray(vaoId);

	// Bind the position VBO, assign it to position 0 on the bound VAO
	// and flag it to be used
	glBindBuffer(GL_ARRAY_BUFFER, positionsVboId);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		3 * sizeof(GLfloat), (void*)0);

	glEnableVertexAttribArray(0);

	// Reset the state
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	

	// COLOURS

	GLuint coloursVboId = 0;

	// Create a new VBO on the GPU and bind it
	glGenBuffers(1, &coloursVboId);

	if (!coloursVboId)
	{
		throw std::exception();
	}

	glBindBuffer(GL_ARRAY_BUFFER, coloursVboId);

	// Upload a copy of the data from memory into the new VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(colours), colours, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE,
		4 * sizeof(GLfloat), (void*)0);

	glEnableVertexAttribArray(1);

	// Reset the state
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	// ====================================== = Preparing the Shader Program ======================================
	std::string vertContent = getFileCode("resources/vertex.txt");
	const GLchar* vertexShaderSrc = vertContent.c_str();
	// Create a new vertex shader, attach source code, compile it and
	// check for errors.
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &vertexShaderSrc, NULL);
	glCompileShader(vertexShaderId);
	GLint success = 0;
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		throw std::exception();
	}

	std::string fragmentShaderfile = getFileCode("resources/fragmentShader.txt");
	const GLchar* fragmentShaderSrc = fragmentShaderfile.c_str();

	// Create a new fragment shader, attach source code, compile it and
	// check for errors.
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &fragmentShaderSrc, NULL);
	glCompileShader(fragmentShaderId);
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		throw std::exception();
	}

	// Create new shader program and attach our shader objects
	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);

	// Ensure the VAO "position" attribute stream gets set as the first position
	// during the link.
	glBindAttribLocation(programId, 0, "in_Position");

	glBindAttribLocation(programId, 1, "in_Colour");

	// Perform the link and check for failure
	glLinkProgram(programId);
	glGetProgramiv(programId, GL_LINK_STATUS, &success);

	if (!success)
	{
		throw std::exception();
	}

	// Detach and destroy the shader objects. These are no longer needed
	// because we now have a complete shader program.
	glDetachShader(programId, vertexShaderId);
	glDeleteShader(vertexShaderId);
	glDetachShader(programId, fragmentShaderId);
	glDeleteShader(fragmentShaderId);




	bool quit = false;

	while (!quit)
	{
		SDL_Event event = { 0 };

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		// Clear red
		glClearColor(1, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		// Update buffers

		// ======================================= SUBMIT FOR DRAWING ======================================
		// Instruct OpenGL to use our shader program and our VAO
		glUseProgram(programId);
		glBindVertexArray(vaoId);

		// Draw 3 vertices (a triangle)
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Reset the state
		glBindVertexArray(0);
		glUseProgram(0);

		SDL_GL_SwapWindow(window);
	}
	return 0;
}