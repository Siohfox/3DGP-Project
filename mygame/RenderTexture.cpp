#include "RenderTexture.h"
#include <exception>

RenderTexture::RenderTexture(int width, int height)
{

	// Generate RenderTexture frame buffers and check if it was made successfully 
	glGenFramebuffers(1, &m_fboId);

	if (!m_fboId) { throw std::exception(); }

	// Bind the frame buffer to the fboId
	glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);

	// Generate textures onto the textureId and bind it
	glGenTextures(1, &m_texId);
	glBindTexture(GL_TEXTURE_2D, m_texId);

	// Set texture params
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texId, 0);

	// Generate render buffers for rbo Id
	glGenRenderbuffers(1, &m_rboId);
	glBindRenderbuffer(GL_RENDERBUFFER, m_rboId);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

	// Unbind again
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rboId);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

RenderTexture::~RenderTexture()
{
	glDeleteFramebuffers(1, &m_fboId);
	glDeleteTextures(1, &m_texId);
	glDeleteRenderbuffers(1, &m_rboId);
}

void RenderTexture::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);
}

void RenderTexture::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}