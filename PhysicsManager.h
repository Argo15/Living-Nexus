#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include "WorldCameraManager.h"
#include "BulletManager.h"

class PhysicsManager {
private:
	WorldCameraManager *worldCameras;
	BulletManager *bulletManager;

public:
	PhysicsManager();
	~PhysicsManager() {}

	void tick(int fps);
	WorldCameraManager *getWorldCameras() {return worldCameras;}
	BulletManager *getBulletManager() {return bulletManager;}
};

#endif