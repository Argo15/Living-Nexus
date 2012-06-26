#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

#include <string>
#include "WorldChunks.h"
#include "ChunkManager.h"
#include "WorldTiles.h"
#include "TileManager.h"
#include "DirectLight.h"
using namespace std;

class WorldManager {
private:
	WorldChunks *worldChunks;
	WorldTiles *worldTiles;
	ChunkManager *chunks;
	TileManager *tiles;
	DirectLight *sun;

public:
	WorldManager();
	~WorldManager() {}

	void tick(int fps);
	void loadWorld(string filename);
	void generateNewWorld(ChunkManager *chunks, TileManager *tiles, PhysicsManager *physicsManager);
	void renderWorld(string shader, Frustum *frustum = 0);

	WorldChunks *getWorldChunks() {return worldChunks;}
	DirectLight *getSun() {return sun;}
};

#endif