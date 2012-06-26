#ifndef WORLDRENDERER_H
#define WORLDRENDERER_H

#include <windows.h>
#include <gl/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Renderer.h"
#include "View.h"
#include "Root.h"
#include "WorldCamera.h"
#include "Frustum.h"
#include "GBuffer.h"
#include "LightBuffer.h"
#include "FinalBuffer.h"
#include "MotionBlurBuffer.h"
#include "AtmosphereBuffer.h"

class GBuffer;
class LightBuffer;
class FinalBuffer;
class MotionBlurBuffer;
class AtmosphereBuffer;

class WorldRenderer : public Renderer{
private:
	View *view;
	WorldCamera *camera;
	Frustum *frustum;
	GBuffer *gBuffer;
	LightBuffer *lightBuffer;
	FinalBuffer *finalBuffer;
	MotionBlurBuffer *motionBlurBuffer;
	AtmosphereBuffer *atmosphereBuffer;

	void forwardRender();
	void defferedRender();

public:
	WorldRenderer();
	~WorldRenderer() {}

	void init();
	void resize(int w, int h);
	void render();

	View *getView() {return view;}
	Frustum *getFrustum() {return frustum;}
};

#endif