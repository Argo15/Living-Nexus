#include "Tile.h"

Tile::Tile() : Chunk() 
{

}

bool Tile::loadTile(string filename) 
{
	return loadChunk(filename);
}

void Tile::drawTile(string shader) 
{
	drawChunk(shader);
}