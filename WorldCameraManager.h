#ifndef WORLDCAMERAMANAGER_H
#define WORLDCAMERAMANAGER_H

#include "WorldCamera.h"

/*
 * Author: wcrane
 * Date: 3/15/2013
 *
 * Manages the different cameras during the world state.
 * For example the default world camera and a debug free-roam camera.
 */
class WorldCameraManager
{
private:
	WorldCamera *m_worldCamera;
	Camera *m_freeRoamCamera;
	Camera *m_current;

public:
	WorldCameraManager();

	void tick(int nFps);
	WorldCamera *getPlayerCamera();
	Camera *getCurrentCamera();
};

#endif