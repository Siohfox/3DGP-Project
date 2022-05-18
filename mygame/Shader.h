#pragma once
#include <GL/glew.h>
#include <string>

class Shader
{
public:
	Shader(const std::string& _vertPath, const std::string& _fragPath);

	GLuint id() {return m_progId; }

private:
	GLuint m_progId;
};

