#include "WorldCameraManager.h"
#include "Root.h"

WorldCameraManager::WorldCameraManager()
{
	worldCamera = new WorldCamera();
	freeRoamCamera = new Camera();
	current = worldCamera;
}

void WorldCameraManager::tick(int fps)
{
	if (Root::inputManager->isKeyDownOnce('c')) {
		if (current == worldCamera) {
			current = freeRoamCamera;
		} else {
			current = worldCamera;
		}
	}
	current->move(120.0/(float)fps);
}