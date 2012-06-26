#include "PhysicsManager.h"

PhysicsManager::PhysicsManager()
{
	worldCameras = new WorldCameraManager();
	bulletManager = new BulletManager();
}

void PhysicsManager::tick(int fps)
{
	bulletManager->tick(fps);
	worldCameras->tick(fps);
}