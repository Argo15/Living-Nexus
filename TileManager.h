#ifndef TILEMANAGER_H
#define TILEMANAGER_H

#include <string>
#include <map>
#include "Tile.h"
using namespace std;

class TileManager {
private:
	map<string,Tile *> tiles;

public:
	TileManager();
	~TileManager(){}

    void Initialize();
	void LoadTile(string filename);
	void DrawTile(string name, string shader);
	void DeleteTile(string name);
	void DeleteAllTiles();

	Tile *getTile(string name) { return tiles[name]; }
	map<string,Tile *> *getTile() {return &tiles;}
};

#endif