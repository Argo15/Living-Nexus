#ifndef SELECTIONBUFFER_H
#define SELECTIONBUFFER_H

#include <windows.h>
#undef __glext_h_
#undef __glxext_h_
#undef __gl_h_
#include <GL/GLee.h>
#include <vector>
#include "View.h"
#include "Matrix.h"
#include "GLSLProgram.h"
#include "Camera.h"
#include "ClickObject.h"
using namespace std;

/*
 * Author: wcrane
 * Date: 5/14/2013
 *
 * Framebuffer Object that renders each ClickObject as a different color.
 */
class SelectionBuffer
{
private:
	GLuint m_nSelectionTex;
	GLuint m_nFrameBuffer;

	int m_nWidth, m_nHeight;
	int m_nSelectedId;

	void getColorFromID(int id, float *color);
	int getIDFromColor(float r, float g, float b);

public:
	SelectionBuffer(int nWidth, int nHeight);
	~SelectionBuffer();

	void drawToBuffer(vector<ClickObject *> *clickObjects, View *view, Camera *camera);

	void bind();
	void unbind();
	void bindSelectionTex();
	GLuint getSelectionTex();
	int getWidth();
	int getHeight();
	int getSelectedObject();
};

#endif