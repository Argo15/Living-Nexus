#include "ShadowMapManager.h"

ShadowMapManager::ShadowMapManager()
{
	sunShadow = new CascadedShadowMap(1024, 0.15f, 0.4f, 0.8f);
}

void ShadowMapManager::tick(int fps)
{
	sunShadow->buildShadowMaps();
}