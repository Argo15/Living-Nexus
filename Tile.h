#ifndef TILE_H
#define TILE_H

#include "Chunk.h"

class Tile : public Chunk {
public:
	Tile();
	~Tile() {}

	bool loadTile(string filename);
	void drawTile(string shader);
};

#endif