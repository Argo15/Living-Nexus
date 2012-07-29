#ifndef CHUNK_H
#define CHUNK_H

#include <string>
#include <iostream>
#include <fstream>
#include "Entity.h"
#include "Actor.h"
#include "PhysicsShape.h"
#include "PhysicsManager.h"
using namespace std;

class Chunk : public Entity, public Transformable {
protected:
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
	Actor **actors;
	int numPhysics;
	PhysicsShape **physics;
	int orientation;
	float radius;
	int tileModes[10][10];
	virtual void drawExtra(string shader) {}

public:
	Chunk();
	~Chunk() {}

	bool loadChunk(string filename);
	void drawChunk(string shader);
	void setOrientation(int ori) {orientation = ori;}
	int getOrientation() {return orientation;}
	float getRadius();
	void addPhysicsToDynamicWorld(PhysicsManager *physicsManager);
	int getTileMode(int x, int y);
	Actor **getActors() {return actors;}
	int getNumActors() {return numActors;}
};

#endif