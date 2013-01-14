#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H

#include <string>
#include <map>
#include "Chunk.h"
using namespace std;

class ChunkManager 
{
private:
	map<string,Chunk *> chunks;

public:
	ChunkManager();

    void Initialize();
	void LoadChunk(string filename);
	void DrawChunk(string name, string shader);
	void DeleteChunk(string name);
	void DeleteAllChunks();

	Chunk *getChunk(string name);
	map<string,Chunk *> *getChunks();
};

#endif