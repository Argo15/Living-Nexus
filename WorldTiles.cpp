#include "WorldTiles.h"
#include "Tree.h"

WorldTiles::WorldTiles(int w, int h)
{
	width = w;
	height = h;
}

void WorldTiles::init()
{
	worldTiles = new TileData**[width];
	for (int i=0; i<width; i++)
	{
		worldTiles[i] = new TileData*[height];
		for (int j=0; j<height; j++)
		{
			worldTiles[i][j] = new TileData();
			worldTiles[i][j]->tileMode = GREEN;
			worldTiles[i][j]->tiles = new vector<Tile *>();
		}
	}
	allTiles = new vector<Tile *>();
}

void WorldTiles::initializeFromChunks(WorldChunks *chunks, TileManager *manager, PhysicsManager *physicsManager)
{
	init();
	for (int i=0; i<(width/10); i++)
	{
		for (int j=0; j<(height/10); j++)
		{
			Chunk *chunk = chunks->getChunk(i,j);
			for (int x=0; x<10; x++)
			{
				for (int y=0; y<10; y++)
				{
					worldTiles[i*10+x][j*10+y]->tileMode = (TileMode) chunk->getTileMode(x,y);
				}
			}
		}
	}
	for (int i=0; i<width; i++)
	{
		for (int j=0; j<height; j++)
		{
			Tile *blockTile = new Tree();
			*blockTile = *(Tree*)manager->getTile("Tree");
			blockTile->Translate(i-5, 0, j-5);
			if (rand() % 50 == 1)
			{
				addTile(i,j,blockTile,physicsManager);
			}
		}
	}
}

vector<Tile *> *WorldTiles::getAllTiles()
{
	return allTiles;
}

vector<Tile *> *WorldTiles::getVisibleTiles(Frustum *frustum)
{
	vector<Tile *> *tiles = new vector<Tile *>();
	for (vector<Tile *>::iterator i = allTiles->begin(); i != allTiles->end(); i++)
	{
		if (frustum->isInFrustum((*i)->getTranslateV(),(*i)->getRadius()))
		{
			tiles->push_back((*i));
		}
	}
	return tiles;
}

bool WorldTiles::addTile(int x, int y, Tile *tile, PhysicsManager *physicsManager)
{
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			int worldX = x+i-5;
			int worldY = y+j-5;
			int tileTileMode = (TileMode) tile->getTileMode(i,j); // tile's local tile modes
			if (worldX >=0 && worldX < 100 && worldY >= 0 && worldY < 100) // inside the tileable zone
			{
				int worldTileMode = (TileMode) worldTiles[worldX][worldY]->tileMode;
				// red and yellow can't hit red or yellow
				if ((tileTileMode == RED || tileTileMode == YELLOW) && (worldTileMode >= RED || worldTileMode == YELLOW))	
				{
					return false;
				}
			}
			else	// outside tileable zone
			{
				if (tileTileMode != 0) // only green allowed here
				{
					return false;
				}
			}
		}
	}

	// success, update the world tile modes
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			int worldX = x+i-5;
			int worldY = y+j-5;
			int tileTileMode = tile->getTileMode(i,j); // tile's local tile modes
			if (worldX >=0 && worldX < 100 && worldY >= 0 && worldY < 100) // inside the tileable zone
			{ 
				if (worldTiles[worldX][worldY]->tileMode == 0)
				{
					worldTiles[worldX][worldY]->tileMode = (TileMode) tileTileMode; // green -> yellow/red
				}
				// red stays red
				// yellow can only update to red
				if (worldTiles[worldX][worldY]->tileMode == 2)
				{
					if (tileTileMode == 1)
					{
						worldTiles[worldX][worldY]->tileMode = (TileMode) tileTileMode; // yellow -> red
					}
				}
			}
		}
	}
	worldTiles[x][y]->tiles->push_back(tile);
	allTiles->push_back(tile);
	tile->addPhysicsToDynamicWorld(physicsManager);
	return true;
}

int WorldTiles::getWidth()
{
	return width;
}

int WorldTiles::getHeight()
{
	return height;
}