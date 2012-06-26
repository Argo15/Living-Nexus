#include "ShadowMapManager.h"

ShadowMapManager::ShadowMapManager()
{
	sunShadow = new CascadedShadowMap(1024);
}

void ShadowMapManager::tick(int fps)
{
	sunShadow->buildShadowMaps();
}