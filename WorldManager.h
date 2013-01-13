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

class WorldManager
{
private:
	WorldChunks *worldChunks;
	WorldTiles *worldTiles;
	ChunkManager *chunks;
	TileManager *tiles;
	DirectLight *sun;

public:
	WorldManager();

	void tick(int fps);
	void loadWorld(string filename);
	void generateNewWorld(ChunkManager *chunks, TileManager *tiles, PhysicsManager *physicsManager);
	void renderWorld(string shader, Frustum *frustum = 0);
	void updateSunToGameTime(GameTime time);

	WorldChunks *getWorldChunks()
	{
		return worldChunks;
	}
	DirectLight *getSun()
	{
		return sun;
	}
};

#endif