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
	WorldCamera *getPlayerCamera()
	{
		return worldCamera;
	}
	Camera *getCurrentCamera()
	{
		return current;
	}
};

#endif