#ifndef SAVETILE_H
#define SAVETILE_H

#include <iostream>
#include <fstream>
#include "ArgoRigidBody.h"
#include "PhysicsShape.h"
using namespace std;

class SaveTile {
public:
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

private: 
	int numActors;
	SaveActor *actors;
	int numPhysics;
	SavePhysics *physics;

	int tileModes[10][10];

public:
	SaveTile() {}
	~SaveTile() {}

	void saveTile(const char *filename);
};

#endif