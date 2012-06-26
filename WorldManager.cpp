#include "WorldManager.h"
#include "Root.h"
#include "WorldState.h"
#include "Camera.h"

WorldManager::WorldManager()
{
	worldChunks = new WorldChunks(10,10);
	worldTiles = new WorldTiles(100,100);
	sun = new DirectLight();
}

void WorldManager::tick(int fps)
{
	if(Root::inputManager->isKeyDownOnce('r')) {
		WorldState *worldState = (WorldState *) Root::GAMESTATE;
		worldState->getPhysicsManager()->getBulletManager()->clearDynamicsWorld();
		worldChunks->generateChunks(chunks, worldState->getPhysicsManager());
		worldTiles->initializeFromChunks(worldChunks, tiles, worldState->getPhysicsManager());
	}
}

void WorldManager::loadWorld(std::string filename)
{
	
}

void WorldManager::generateNewWorld(ChunkManager *chunks, TileManager *tiles, PhysicsManager *physicsManager)
{
	worldChunks->generateChunks(chunks, physicsManager);
	worldTiles->initializeFromChunks(worldChunks, tiles, physicsManager);
	this->chunks = chunks;
	this->tiles = tiles;
}

void WorldManager::renderWorld(string shader, Frustum *frustum)
{
	WorldState *worldState = (WorldState *) Root::GAMESTATE;
	if (frustum == 0)
		frustum = worldState->getRenderer()->getFrustum();
	vector<Chunk *> *visChunks = worldChunks->getVisibleChunks(frustum);
	for (vector<Chunk *>::iterator i = visChunks->begin(); i != visChunks->end(); i++) {
		(*i)->drawChunk(shader);
	}
	vector<Tile *> *visTiles = worldTiles->getVisibleTiles(frustum);
	for (vector<Tile *>::iterator i = visTiles->begin(); i != visTiles->end(); i++) {
		(*i)->drawTile(shader);
	}
}