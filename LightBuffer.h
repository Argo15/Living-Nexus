#ifndef LIGHTBUFFER_H
#define LIGHTBUFFER_H

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

class LightBuffer 
{
private:
	GLuint lightTex;
	GLuint glowTex;
	GLuint buffer;

	int width,height;

public:
	LightBuffer(int width, int height);
	~LightBuffer();

	void drawToBuffer(GLuint normalTex, GLuint depthTex, GLuint glowTex, View *view);

	void bind();
	void unbind();
	void bindLightTex();
	void bindGlowTex();
	GLuint getLightTex();
	GLuint getGlowTex();
	int getWidth();
	int getHeight();
};

#endif