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

/*
 * Author: wcrane
 * Date: 3/17/2013
 *
 * Framebuffer Object holding the final color buffer for rendering.
 */
class FinalBuffer
{
private:
	GLuint m_nFinalTex;
	GLuint m_nFrameBuffer;

	int m_nWidth, m_nHeight;

public:
	FinalBuffer(int nWidth, int nHeight);
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