#include "Shader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

std::string load_file(const std::string _path)
{
	std::ifstream file(_path.c_str());

	if(!file.is_open())
	{
		throw std::runtime_error("Failed to open file");
	}

	std::string rtn;
	std::string line;
	while (!file.eof())
	{
		std::getline(file, line);

		rtn += line + '\n';
	}

	return rtn;
}

Shader::Shader(const std::string& _vertPath, const std::string& _fragPath)
{
	/////////////////////////////////////////////////////////////////////////////////////////////////
	// Vertex Shader
	/////////////////////////////////////////////////////////////////////////////////////////////////
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	std::string src = load_file(_vertPath);
	const char* psrc = src.c_str();
	glShaderSource(vertexShaderId, 1, &psrc, NULL);
	glCompileShader(vertexShaderId);
	GLint success = 0;
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		throw std::runtime_error("Failed to compile vertex shader");
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////
	// Fragment Shader
	/////////////////////////////////////////////////////////////////////////////////////////////////
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	src = load_file(_fragPath);
	psrc = src.c_str();
	glShaderSource(fragmentShaderId, 1, &psrc, NULL);
	glCompileShader(fragmentShaderId);
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
	if (!success) { throw std::runtime_error("Failed to compile fragment shader"); }

	/////////////////////////////////////////////////////////////////////////////////////////////////
	// Bind Shaders
	/////////////////////////////////////////////////////////////////////////////////////////////////
	m_progId = glCreateProgram();
	glAttachShader(m_progId, vertexShaderId);
	glAttachShader(m_progId, fragmentShaderId);
	// Ensure the VAO "position" attribute stream gets set as the first position during the link.
	glBindAttribLocation(m_progId, 0, "a_Position");
	glBindAttribLocation(m_progId, 1, "a_TexCoord");
	glBindAttribLocation(m_progId, 2, "a_Normal");
	// Perform the link and check for failure
	glLinkProgram(m_progId);
	glGetProgramiv(m_progId, GL_LINK_STATUS, &success);
	if (!success) {	throw std::exception("Failed to link program"); }

	/////////////////////////////////////////////////////////////////////////////////////////////////
	// Detatch And Destroy
	/////////////////////////////////////////////////////////////////////////////////////////////////
	glDetachShader(m_progId, vertexShaderId);
	glDeleteShader(vertexShaderId);
	glDetachShader(m_progId, fragmentShaderId);
	glDeleteShader(fragmentShaderId);
}

GLuint Shader::id()
{
	return m_progId;
}