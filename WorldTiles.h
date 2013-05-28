#ifndef WORLDTILES_H
#define WORLDTILES_H

#include <vector>
#include "Tree.h"
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

/*
 * Author: wcrane
 * Date: 3/15/2013
 *
 * Object to manage and hold the tiles in a world.
 */
class WorldTiles
{
private:
	struct TileData
	{
		TileMode tileMode; 
		vector<Tile *> *tiles;
	};

	int m_nWidth, m_nHeight;
	TileData ***m_worldTiles;
	vector<Tile *> *m_allTiles;
	vector<Tree *> *m_trees;
	Tile *m_fruitStand;

public:
	WorldTiles(int nWidth, int nHeight);

	void init();
	void initializeFromChunks(WorldChunks *chunks, PhysicsManager *physicsManager);
	bool addTile(int nPosX, int nPosY, Tile *tile, PhysicsManager *physicsManager);
	void addClickObjects(Camera *camera);
	vector<Tile *> *getAllTiles();
	vector<Tile *> *getVisibleTiles(Frustum *frustum);
	int getWidth();
	int getHeight();
};

#endif