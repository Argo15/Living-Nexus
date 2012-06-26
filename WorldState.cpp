#include "WorldState.h"
#include "Matrix.h"

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

	// get time
	time_t t = time(0);
    struct tm * now = localtime( & t );
	std::string pm = "am";
	if (now->tm_hour >= 12) {
		pm = "pm";
		now->tm_hour -= 12;
	}
	if (now->tm_hour == 0) {
		now->tm_hour = 12;
	}
	printf("Time: %d:%d:%d %d/%d/%d \r",now->tm_hour, now->tm_min, now->tm_sec, now->tm_mon+1, now->tm_mday, now->tm_year+1900);

	physicsManager->tick(fps);
	worldManager->tick(fps);
	shadowMapManager->tick(fps);
	renderer->render();
}