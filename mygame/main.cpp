// Tell system that SDL and STB IMAGE is already handled
#define SDL_MAIN_HANDLED
#define STB_IMAGE_IMPLEMENTATION

// Graphics libraries
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

			fileContent += line + "\n";
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
	  -0.5f, 0.5f, 0.0f,
	  -0.5f, -0.5f, 0.0f,
	  0.5f, -0.5f, 0.0f,

	   0.5f, -0.5f, 0.0f,
	  0.5f, 0.5f, 0.0f,
	  -0.5f, 0.5f, 0.0f
	};

	const GLfloat texCoords[] = {
	  0.0f, 0.0f,
	  0.0f, 1.0f,
	  1.0f, 1.0f,

	  1.0f, 1.0f,
	  1.0f, 0.0f,
	  0.0f, 0.0f
	};

	// RGBA - Vector 4
	const GLfloat colours[] = {
	  1.0f, 0.0f, 0.0f, 1.0f,
	  0.0f, 1.0f, 0.0f, 1.0f,
	  0.0f, 0.0f, 1.0f, 1.0f,
	};


	/*
		Create and populate positions buffer
	*/

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

	/*
		Create and populate colours buffer
	*/

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

		/*
			Create the vertex array and assign positions and colours
		*/


	GLuint texCoordsVboID = 0;

	// Create a new VBO on the GPU and bind it
	glGenBuffers(1, &texCoordsVboID);

	if (!texCoordsVboID)
	{
		throw std::exception();
	}

	glBindBuffer(GL_ARRAY_BUFFER, texCoordsVboID);

	// Upload a copy of the data from memory into the new VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);

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

	// This is where it's attached to the vertex array buffer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		3 * sizeof(GLfloat), (void*)0);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, coloursVboId);

	// This is where it's attached to the vertex array buffer
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE,
		4 * sizeof(GLfloat), (void*)0);

	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, texCoordsVboID);

	// This is where it's attached to the vertex array buffer
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
		2 * sizeof(GLfloat), (void*)0);

	glEnableVertexAttribArray(2);

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
	glBindAttribLocation(programId, 0, "a_Position");

	glBindAttribLocation(programId, 2, "a_TexCoord");

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


	GLint modelLoc = glGetUniformLocation(programId, "u_Model");
	GLint projectionLoc = glGetUniformLocation(programId, "u_Projection");

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


		/*
			Uploading to graphics card
		*/


	// Create a texture
	GLuint textureId = 0;
	glGenTextures(1, &textureId);

	if (!textureId)
	{
		std::cout << "ERROR: No texture ID found" << std::endl;
		throw std::exception();
	}

	// Bind the texture to GPU
	glBindTexture(GL_TEXTURE_2D, textureId);


	// Upload the image data to the bound texyture unit in the GPU
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	// Free the loaded data because it's copied to gpu now
	free(data);

	// Generate Mipmap so the texture can be mapped correctly
	glGenerateMipmap(GL_TEXTURE_2D);

	// Unbind the texture because we're done with it
	glBindTexture(GL_TEXTURE_2D, 0);








	// MAIN LOOP

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

		// Clear black
		glClearColor(1, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		// Update buffers

		// Prepare the perspective projection matrix
		glm::mat4 projection = glm::perspective(glm::radians(45.0f),
			(float)600 / (float)600, 0.1f, 100.f);

		// Prepare the model matrix
		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0, 0, -2.5f));
		model = glm::rotate(model, glm::radians(angle), glm::vec3(0, 1, 0));

		// Increase the float angle so next frame the triangle rotates further
		angle += 1.0f;

		// Make sure the current program is bound
#
		// Instruct OpenGL to use our shader program and our VAO
		glUseProgram(programId);
		glBindVertexArray(vaoId);
		glBindTexture(GL_TEXTURE_2D, textureId);

		// Upload the model matrix
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		// Upload the projection matrix
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE,
		glm::value_ptr(projection));

		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// Shape 2

		// Prepare the orthographic projection matrix (reusing the variable)
		projection = glm::ortho(0.0f, (float)600, 0.0f,
			(float)600, 0.0f, 1.0f);

			// Prepare model matrix. The scale is important because now our triangle
			// would be the size of a single pixel when mapped to an orthographic
			// projection.
			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(100, 600 - 100, 0));
			model = glm::scale(model, glm::vec3(100, 100, 1));

			// Upload the model matrix
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			// Upload the projection matrix
			glUniformMatrix4fv(projectionLoc, 1, GL_FALSE,
				glm::value_ptr(projection));

		// ======================================= SUBMIT FOR DRAWING ======================================
		
		// Draw 3 vertices (a triangle)
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// Reset the state
		glBindVertexArray(0);
		glUseProgram(0);

		// This function just updates the window
		SDL_GL_SwapWindow(window);
	}
	return 0;
}