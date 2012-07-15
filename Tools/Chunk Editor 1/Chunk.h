#ifndef CHUNK_H
#define CHUNK_H

#include "Tile.h"

class Chunk {
private:
	Tile *tiles[10][10];
	int rotate[10][10];
	bool canUpdate[10][10];

	int selectedX, selectedZ;
	Tile *currentTile;
	int currentRotate;

public:
	Chunk();
	~Chunk();

	int tileMode[10][10];

	void drawChunk(GLSLProgram *program);
	void update(int mouseX, int mouseY, bool mouseClick);
	void setCurrentTile(Tile *tile) {currentTile = tile;}
	void setCurrentRotate(int rotate) {currentRotate = rotate;}
};

#endif