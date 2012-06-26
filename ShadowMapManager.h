#ifndef SHADOWMAPMANAGER_H
#define SHADOWMAPMANAGER_H

#include "CascadedShadowMap.h"

class CascadedShadowMap;

class ShadowMapManager {
private:
	CascadedShadowMap *sunShadow;

public:
	ShadowMapManager();
	~ShadowMapManager() {}

	void tick(int fps);

	CascadedShadowMap *getSunShadow() {return sunShadow;}
};

#endif