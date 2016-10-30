#ifndef DEPTHBUFFER_H
#define DEPTHBUFFER_H

#include <windows.h>
#include <gl/glee.h>

/*
 * Author: wcrane
 * Date: 3/17/2013
 *
 * Framebuffer Object holding depth information
 */
class DepthBuffer
{
protected:
	GLuint m_nTexture;
	GLuint m_FrameBuffer;

public:
	DepthBuffer(int nWidth, int nHeight);
	void bind();
	void unbind();
	GLuint getBuffer();
	GLuint getTexture();
};
#endif