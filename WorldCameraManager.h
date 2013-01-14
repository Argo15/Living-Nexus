#ifndef WORLDCAMERAMANAGER_H
#define WORLDCAMERAMANAGER_H

#include "WorldCamera.h"

class WorldCameraManager
{
private:
	WorldCamera *worldCamera;
	Camera *freeRoamCamera;
	Camera *current;

public:
	WorldCameraManager();

	void tick(int fps);
	WorldCamera *getPlayerCamera();
	Camera *getCurrentCamera();
};

#endif