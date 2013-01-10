#include "WorldManager.h"
#include "Root.h"
#include "WorldState.h"
#include "Camera.h"
#include "GameState.h"

static Vector3 V_SUN_QUATERNION(2.0f,0.0f,-1.0f);

WorldManager::WorldManager()
{
	worldChunks = new WorldChunks(10,10);
	worldTiles = new WorldTiles(100,100);
	sun = new DirectLight();
}

void WorldManager::tick(int fps)
{
	updateSunToGameTime(TimeManager::getInstance()->getGameTime());
	if(Root::inputManager->isKeyDownOnce('r')) {
		WorldState *worldState = (WorldState *) GameState::GAMESTATE;
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
	WorldState *worldState = (WorldState *) GameState::GAMESTATE;
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

void WorldManager::updateSunToGameTime(GameTime time) {
	float angle = (time.getHours()/24.0f + time.getMinutes()/60.0f/24.0f + time.getSeconds()/60.0f/60.0f/24.0f) - 0.5f;
	Quaternion quat;
	quat.createQuaternion(angle*(2*3.1415), V_SUN_QUATERNION);
	sun->setRotate(quat);
}