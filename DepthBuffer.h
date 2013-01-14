#ifndef DEPTHBUFFER_H
#define DEPTHBUFFER_H

#include <windows.h>
#include <gl/glee.h>

class DepthBuffer
{
protected:
	GLuint texture;
	GLuint buffer;

public:
	DepthBuffer(int width, int height);
	void bind();
	void unbind();
	GLuint getBuffer();
	GLuint getTexture();
};
#endif