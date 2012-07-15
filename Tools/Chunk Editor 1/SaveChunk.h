#ifndef SAVECHUNK_H
#define SAVECHUNK_H

#include <iostream>
#include <fstream>
#include "PhysicsShape.h"
using namespace std;

class SaveChunk {
private: 
	struct SaveActor
	{
		char name[100];
		char model[100];
		char material[100];

		float translation[3];
		float rotation[4];
		float scale[3];
	};

	struct SavePhysics
	{
		float translation[3];
		float rotation[4];
		float scale[3];
		PhysicsShapeType physicsType;
	};

	int numActors;
	SaveActor *actors;
	int numPhysics;
	SavePhysics *physics;
	int tileModes[10][10];

public:
	SaveChunk() {}
	~SaveChunk() {}

	void saveChunk(const char *filename);
};

#endif