#ifndef WORLDTILES_H
#define WORLDTILES_H

#include <vector>
#include "Tile.h"
#include "TileManager.h"
#include "WorldChunks.h"
#include "Frustum.h"
using namespace std;

enum TileMode
{
	GREEN,
	RED,
	YELLOW
};

class WorldTiles
{
private:
	struct TileData
	{
		TileMode tileMode; 
		vector<Tile *> *tiles;
	};

	int width, height;
	TileData ***worldTiles;
	vector<Tile *> *allTiles;

public:
	WorldTiles(int w, int h);

	void init();
	void initializeFromChunks(WorldChunks *chunks, TileManager *manager, PhysicsManager *physicsManager);
	bool addTile(int x, int y, Tile *tile, PhysicsManager *physicsManager);
	vector<Tile *> *getAllTiles();
	vector<Tile *> *getVisibleTiles(Frustum *frustum);
	int getWidth();
	int getHeight();
};

#endif