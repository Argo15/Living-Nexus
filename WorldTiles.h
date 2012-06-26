#ifndef WORLDTILES_H
#define WORLDTILES_H

#include <vector>
#include "Tile.h"
#include "TileManager.h"
#include "WorldChunks.h"
#include "Frustum.h"
using namespace std;

class WorldTiles {
private:
	struct TileData {
		int tileMode; // 0=green, 1=red, 2=yellow
		vector<Tile *> *tiles;
	};

	int width, height;
	TileData ***worldTiles;
	vector<Tile *> *allTiles;

public:
	WorldTiles(int w, int h);
	~WorldTiles() {}

	void init();
	void initializeFromChunks(WorldChunks *chunks, TileManager *manager, PhysicsManager *physicsManager);
	bool addTile(int x, int y, Tile *tile, PhysicsManager *physicsManager);
	vector<Tile *> *getAllTiles();
	vector<Tile *> *getVisibleTiles(Frustum *frustum);
	int getWidth() {return width;}
	int getHeight() {return height;}

};

#endif