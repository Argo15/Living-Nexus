#ifndef TILE
#define TILE

#include <vector>
#include "ArgoActor.h"
#include "GLSLProgram.h"
using namespace std;

class Tile 
{
private:
	vector<ArgoActor *> actors;
	QString name;

public:
	Tile(QString name) {this->name = name;}
	~Tile() {}

	void addActor(ArgoActor *actor) {actors.push_back(actor);}
	void drawTileSelection();
	void drawTile(GLSLProgram *program);
	QString getName() {return name;}
};

#endif