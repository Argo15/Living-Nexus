#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

#include <string>
#include "WorldChunks.h"
#include "ChunkManager.h"
#include "WorldTiles.h"
#include "TileManager.h"
#include "DirectLight.h"
#include "TimeManager.h"
#include "GameTime.h"
using namespace std;

/*
 * Author: wcrane
 * Date: 3/15/2013
 *
 * Manages components of the world. This includes the tiles and chunks.
 */
class WorldManager
{
private:
	WorldChunks *m_worldChunks;
	WorldTiles *m_worldTiles;
	DirectLight *m_sun;

public:
	WorldManager();

	void tick(int nFps);
	void loadWorld(string sFilename);
	void generateNewWorld(PhysicsManager *physicsManager);
	void renderWorld(string sShader, Frustum *frustum = 0);
	void updateSunToGameTime(GameTime time);

	WorldChunks *getWorldChunks();
	DirectLight *getSun();
};

#endif