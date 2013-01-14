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
	~MotionBlurBuffer();

	void drawToBuffer(GLuint texture, GLuint velocityTex, int numSamples, View *view);

	void bind();
	void unbind();
	void bindBlurTex();
	GLuint getBlurTex();
	int getWidth();
	int getHeight();
};

#endif