#include "WorldState.h"
#include "Matrix.h"
#include "TimeManager.h"

WorldState::WorldState(const char *filename)
{ 
	physicsManager = new PhysicsManager();
	chunkManager = new ChunkManager();
	chunkManager->Initialize();
	tileManager = new TileManager();
	tileManager->Initialize();
	renderer = new WorldRenderer();
	renderer->init();
	glutSetCursor(GLUT_CURSOR_NONE);

	worldManager = new WorldManager();
	if (filename == 0) {
		worldManager->generateNewWorld(chunkManager,tileManager,physicsManager);
	} else {
		worldManager->loadWorld(string(filename));
	}

	shadowMapManager = new ShadowMapManager();

	mouseHide = true;
}

WorldState::~WorldState()
{

}

void WorldState::resize(int w, int h)
{
	renderer->resize(w, h);
}

void WorldState::tick(int fps)
{
	if (Root::inputManager->isKeyDownOnce((int)'t')) {
		mouseHide = !mouseHide;
		if (mouseHide)
			glutSetCursor(GLUT_CURSOR_NONE);
		else
			glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
	}

	physicsManager->tick(fps);
	worldManager->tick(fps);
	shadowMapManager->tick(fps);
	renderer->render();
}