#ifndef MOTIONBLURBUFFER_H
#define MOTIONBLURBUFFER_H

#include <windows.h>
#undef __glext_h_
#undef __glxext_h_
#undef __gl_h_
#include <GL/GLee.h>
#include <vector>
#include "View.h"
#include "Texture.h"
#include "Matrix.h"
#include "GLSLProgram.h"
#include "Camera.h"
#include "WorldState.h"
using namespace std;

class MotionBlurBuffer
{
private:
	GLuint blurTex;
	GLuint buffer;

	int width,height;

public:
	MotionBlurBuffer(int width, int height);
	~MotionBlurBuffer()
	{
		glDeleteFramebuffers(1,&buffer);
	}

	void drawToBuffer(GLuint texture, GLuint velocityTex, int numSamples, View *view);

	void bind() 
	{
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, buffer);
	}
	void unbind() 
	{
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	}

	void bindBlurTex() 
	{
		glBindTexture(GL_TEXTURE_2D, blurTex);
	}

	GLuint getBlurTex() 
	{
		return blurTex;
	}

	int getWidth() 
	{
		return width;
	}
	int getHeight() 
	{
		return height;
	}
};

#endif