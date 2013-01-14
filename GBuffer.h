#ifndef GBUFFER_H
#define GBUFFER_H

#include <windows.h>
#undef __glext_h_
#undef __glxext_h_
#undef __gl_h_
#include <GL/GLee.h>
#include <vector>
#include "Chunk.h"
#include "WorldState.h"
#include "Camera.h"
#include "Frustum.h"
#include "View.h"
using namespace std;

class GBuffer 
{
private:
	GLuint depthTex;
	GLuint normalTex;
	GLuint colorTex;
	GLuint worldPosTex;
	GLuint glowTex;
	GLuint motionTex;
	GLuint buffer;

	int width,height;
	Camera lastCamera;
	glm::mat4 lastCameraProj;

public:
	GBuffer(int width, int height);
	~GBuffer();

	void drawToBuffer(View *view);

	void bind();
	void unbind();

	void bindDepthTex();
	void bindNormalTex();
	void bindColorTex();
	void bindPositionTex();
	void bindGlowTex();
	void bindMotionTex();

	GLuint getGlowTex();
	GLuint getDepthTex();
	GLuint getColorTex();
	GLuint getNormalTex();
	GLuint getWorldPosTex();
	GLuint getMotionTex();

	int getWidth();
	int getHeight();
};

#endif