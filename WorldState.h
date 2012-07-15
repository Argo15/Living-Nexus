#ifndef WORLDSTATE_H
#define WORLDSTATE_H

#include <string>
#include "GameState.h"
#include "ChunkManager.h"
#include "TileManager.h"
#include "WorldRenderer.h"
#include "PhysicsManager.h"
#include "WorldManager.h"
#include "ShadowMapManager.h"

class WorldRenderer;
class ShadowMapManager;

class WorldState : public GameState
{
private:
	ChunkManager *chunkManager;
	TileManager *tileManager;
	WorldRenderer *renderer;
	PhysicsManager *physicsManager;
	WorldManager *worldManager;
	ShadowMapManager *shadowMapManager;

	bool mouseHide;

public:
	WorldState(const char *filename = 0);
	~WorldState();

	virtual void resize(int w, int h);
	virtual void tick(int fps);

	virtual bool mouseHidden() {return mouseHide;}

	ChunkManager *getChunkManager() {return chunkManager;}
	PhysicsManager *getPhysicsManager() {return physicsManager;}
	WorldManager *getWorldManager() {return worldManager;}
	WorldRenderer *getRenderer() {return renderer;}
	ShadowMapManager *getShadowMapManager() {return shadowMapManager;}
	TileManager *getTileManager() {return tileManager;}
};
#endif