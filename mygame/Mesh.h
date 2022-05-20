#pragma once
#include <GL/glew.h>

class Mesh
{
public:

	/** A constructor of the Mesh 
	*/
	Mesh();

	/** Get the vao ID
	* @return the vao ID as a GLuint
	*/
	GLuint GetVaoID() { return m_vaoId; }

	/** Get the vertex count
	* @return the vertex count as an integer
	*/
	int VertCount();

private:

	/** The Mesh's Vbo Id
	*/
	GLuint m_posVboId;

	/** The Mesh's Vao Id
	*/
	GLuint m_vaoId;
};

