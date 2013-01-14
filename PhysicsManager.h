#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include "WorldCameraManager.h"
#include "BulletManager.h"

class PhysicsManager 
{
private:
	WorldCameraManager *worldCameras;
	BulletManager *bulletManager;

public:
	PhysicsManager();

	void tick(int fps);
	WorldCameraManager *getWorldCameras();
	BulletManager *getBulletManager();
};

#endif