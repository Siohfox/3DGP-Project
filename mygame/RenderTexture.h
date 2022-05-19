#pragma once
#include <GL/glew.h>

class RenderTexture
{
public:
	/** A constructor for RenderTexture
	* @param int width the width of the window
	* @param int height the height of the window
	*/
	RenderTexture(int width, int height);

	/** A destructor for RenderTexture
	*/
	~RenderTexture();


	/** A fuction to bind the fbo Id
	*/
	void bind();

	/** A fuction to unbind the fbo Id
	*/
	void unbind();


	/** Get the texture Id
	* @return the Texture Id
	*/
	GLuint GetTexture() { return m_texId; }

private:
	/** A texture fbo Id
	*/
	GLuint m_fboId;

	/** A texture Id
	*/
	GLuint m_texId;

	/** A texture rbo Id
	*/
	GLuint m_rboId;
};

