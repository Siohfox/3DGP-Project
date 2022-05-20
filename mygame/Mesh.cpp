#include "Mesh.h"
#include <exception>

/** A way of telling the program how to draw the mesh via positions
*/
const GLfloat positions[] = {
	-1.0, 1.0f, 0.0f,
	-1.0f, -1.0f, 0.0f,
	 1.0f, -1.0f, 0.0f,

	 1.0, -1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	 -1.0f, 1.0f, 0.0f,
};

Mesh::Mesh()
{
	// Generate buffers for positionVboId and check if successful, then bind
	glGenBuffers(1, &m_posVboId);
	if (!m_posVboId) { throw std::exception(); }
	glBindBuffer(GL_ARRAY_BUFFER, m_posVboId);

	// Buffer position data using position locations
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	// Unbind buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Generate vertex arrays to vaoId and check if successful
	glGenVertexArrays(1, &m_vaoId);
	if (!m_vaoId) { throw std::exception(); }
	glBindVertexArray(m_vaoId);

	// Bind array to position vboId
	glBindBuffer(GL_ARRAY_BUFFER, m_posVboId);

	// Define an array of generic vertex attribute data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Unbind
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

int Mesh::VertCount()
{
	return 6;
}