#ifndef FINALBUFFER_H
#define FINALBUFFER_H

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

class FinalBuffer
{
private:
	GLuint finalTex;
	GLuint buffer;

	int width,height;

public:
	FinalBuffer(int width, int height);
	~FinalBuffer();

	void drawToBuffer(GLuint colorTex, GLuint lightTex, GLuint glowTex, View *view);

	void bind();
	void unbind();
	void bindFinalTex();
	GLuint getFinalTex();
	int getWidth();
	int getHeight();
};

#endif