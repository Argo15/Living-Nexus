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
#include "InventoryGui.h"
#include "WorldHud.h"

class WorldRenderer;
class ShadowMapManager;

/*
 * Author: wcrane
 * Date: 3/15/2013
 *
 * State object for when the user is exploring the world.
 */
class WorldState : public GameState
{
private:
	WorldRenderer *m_renderer;
	PhysicsManager *m_physicsManager;
	WorldManager *m_worldManager;
	ShadowMapManager *m_shadowMapManager;
	
	WorldHud *m_worldHud;
	InventoryGui *m_inventoryGui;
	SquareFrame *m_inventoryFrame;

	bool m_bMovementEnabled;
	bool m_bMouseHide;
	void toggleMouse();

public:
	static WorldState* getInstance();

	WorldState(const char *sFilename = 0);
	~WorldState();

	virtual void resize(int nWidth, int nHeight);
	virtual void tick(int nFps);

	virtual bool mouseHidden();

	PhysicsManager *getPhysicsManager();
	WorldManager *getWorldManager();
	WorldRenderer *getRenderer();
	ShadowMapManager *getShadowMapManager();

	InventoryGui *getInventory();
	void toggleInventory();
};
#endif