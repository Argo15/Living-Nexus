#ifndef	WORLDCHUNKS
#define WORLDCHUNKS

#include <vector>
#include "Chunk.h"
#include "ChunkManager.h"
#include "Frustum.h"
using namespace std;

class WorldChunks
{
private:
	int width, height;
	Chunk ***worldChunks;
	vector<Chunk *> *allChunks;

public:
	WorldChunks(int w, int h);

	void generateChunks(ChunkManager *chunks, PhysicsManager *physicsManager);
	vector<Chunk *> *getAllChunks();
	vector<Chunk *> *getVisibleChunks(Frustum *frustum);
	Chunk *getChunk(int x, int y)
	{
		return worldChunks[x][y];
	}

	int getWidth()
	{
		return width;
	}
	int getHeight()
	{
		return height;
	}
};

#endif