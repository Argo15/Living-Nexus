#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <vector>
#include "Actor.h"
#include "Tile.h"
#include "TileManager.h"
#include "ChunkManager.h"
#include "Logger.h"
#include "Transformer.h"

class Transformer;

class SceneManager {
private:
	static SceneManager *m_pInstance;
	std::map<int, Actor *> *actors;		// ActorId -> Actor
	int nextActorId;
	TileManager *tileManager;
	ChunkManager *chunkManager;
	int selectedActorId;
	SceneManager();

public:
	static SceneManager *getInstance();
	int addActor(Actor *actor);			// returns an actorId
	void removeActor(int actorId);
	void addChunk(Chunk *chunk);
	void addChunk(string chunk);
	void addTile(string tile);
	void clear();
	void draw();
	void drawTransformers();
	void setSelectedActor(int id) {selectedActorId = id;}
	Actor *getSelectedActor();
	std::map<int, Actor *> *getActors() {return actors;}

	TileManager *getTileManager() {return tileManager;}
	ChunkManager *getChunkManager() {return chunkManager;}
};

#endif