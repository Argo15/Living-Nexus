#ifndef ATMOSPHEREBUFFER_H
#define ATMOSPHEREBUFFER_H

#include <windows.h>
#undef __glext_h_
#undef __glxext_h_
#undef __gl_h_
#include <GL/GLee.h>
#include <vector>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "Chunk.h"
#include "WorldState.h"
#include "Camera.h"
#include "Frustum.h"
#include "View.h"
#include "TimeManager.h"
#include "Config.h"
#include "Matrix.h"
#include "MathUtils.h"
#include "TimeUtils.h"
using namespace std;

class AtmosphereBuffer {
private:
	GLuint colorTex;
	GLuint glowTex;
	GLuint buffer;

	int width,height;

public:
	AtmosphereBuffer(int width, int height);
	~AtmosphereBuffer(){glDeleteFramebuffers(1,&buffer);}

	void drawToBuffer(GLuint colorBuf, GLuint glowBuf, GLuint depthBuf, View *view);

	void bind() {glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, buffer);}
	void unbind() {glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);}

	void bindColorTex() {glBindTexture(GL_TEXTURE_2D, colorTex);}
	void bindGlowTex() {glBindTexture(GL_TEXTURE_2D, glowTex);}

	GLuint getGlowTex() {return glowTex;}
	GLuint getColorTex() {return colorTex;}

	int getWidth() {return width;}
	int getHeight() {return height;}
	
	Vector3 getNearSunColor();
	Vector3 getAwaySunColor();
	Vector3 getCloudColor();
};

#endif