#pragma once
#include <GL/glew.h>
#include <string>

class Shader
{
public:
	/** A constructor for Shader
	* @param const std::string& _vertPath a vertex shader path to read from file
	* @param const std::string& _fragPath a fragment shader path to read from file
	*/
	Shader(const std::string& _vertPath, const std::string& _fragPath);

	/** Get shader program Id
	* @return shader's program Id
	*/
	GLuint shaderProgramId() {return m_progId; }

private:
	/** Program Id
	*/
	GLuint m_progId;
};

