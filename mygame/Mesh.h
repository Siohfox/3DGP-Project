#pragma once
#include <GL/glew.h>

struct Mesh
{
	Mesh(int _type);

	GLuint getid();

	int vert_count();

private:
	GLuint m_posVboId;
	GLuint m_vaoId;
	

};

