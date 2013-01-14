#ifndef CASCADEDSHADOWMAP_H
#define CASCADEDSHADOWMAP_H

#include "DepthBuffer.h"
#include "Frustum.h"
#include "Camera.h"
#include "View.h"
#include "DirectLight.h"
#include "WorldState.h"

class CascadedShadowMap
{
private:
	DepthBuffer *shadowMaps[4];
	glm::mat4 lightMatrix[4];
	float slices[3];
	int size;

	Camera *createLightCamera(float slice1, float slice2, Camera *camera, View *view, DirectLight *dLight);
	View *createLightView(float slice1, float slice2, Camera *camera, Camera *lightCamera, View *view, Frustum *frustum);

public:
	CascadedShadowMap();
	CascadedShadowMap(int size, float slice1 = 0.15, float slice2 = 0.3, float slice3 = 0.6);

	void buildShadowMaps();
	void bindShadowMap(int map);
	void sendToShader(string shader);

	void drawShadowMaps();
};

#endif