#ifndef TILEMANAGER_H
#define TILEMANAGER_H

#include "Tile.h"
#include <vector>
using namespace std;

class TileManager {
public:
    static TileManager* Instance();
    static void Initialize();
	void LoadTile(const char *filename);

	Tile *getTile(QString name);
	vector<Tile*> *getTiles() {return &tiles;}

	~TileManager(){}
private:
	vector<Tile*> tiles;

	TileManager();
    static TileManager* pInstance;
};

#endif