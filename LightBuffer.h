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
	~LightBuffer(){glDeleteFramebuffers(1,&buffer);}

	void drawToBuffer(GLuint normalTex, GLuint depthTex, GLuint glowTex, View *view);

	void bind() {glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, buffer);}
	void unbind() {glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);}

	void bindLightTex() {glBindTexture(GL_TEXTURE_2D, lightTex);}
	void bindGlowTex() {glBindTexture(GL_TEXTURE_2D, glowTex);}

	GLuint getLightTex() {return lightTex;}
	GLuint getGlowTex() {return glowTex;}

	int getWidth() {return width;}
	int getHeight() {return height;}
};

#endif