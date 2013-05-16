#include "WorldState.h"
#include "Matrix.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "InventoryGui.h"
#include "GuiManager.h"

WorldState::WorldState(const char *sFilename)
{ 
	m_physicsManager = new PhysicsManager();
	m_chunkManager = new ChunkManager();
	m_chunkManager->initialize();
	m_tileManager = new TileManager();
	m_tileManager->initialize();
	m_renderer = new WorldRenderer();
	m_renderer->init();
	glutSetCursor(GLUT_CURSOR_NONE);

	m_worldManager = new WorldManager();
	if (sFilename == 0)
	{
		m_worldManager->generateNewWorld(m_chunkManager, m_tileManager, m_physicsManager);
	}
	else
	{
		m_worldManager->loadWorld(string(sFilename));
	}

	m_shadowMapManager = new ShadowMapManager();

	m_bMouseHide = true;
	m_bMovementEnabled = true;

	m_inventoryGui = new InventoryGui();
	m_guiFrame = new SquareFrame();
	m_worldHud = new WorldHud();

	m_guiFrame->addElement(m_inventoryGui);
}

WorldState::~WorldState()
{

}

void WorldState::resize(int nWidth, int nHeight)
{
	m_renderer->resize(nWidth, nHeight);
	m_guiFrame->initialize(m_renderer->getView());
	m_worldHud->initialize(m_renderer->getView());
}

void WorldState::tick(int nFps)
{
	if (InputManager::getInstance()->isKeyDownOnce((int)'t'))
	{
		toggleMouse();
	}
	// Open inventory
	if (InputManager::getInstance()->isKeyDownOnce((int)'f'))
	{
		m_inventoryGui->initialize();
		toggleMouse();
		m_bMovementEnabled = !m_bMovementEnabled;
	}
	if (m_bMovementEnabled)
	{
		GuiManager::getInstance()->setRootElement(m_worldHud);
		m_physicsManager->tick(nFps);
	}
	else
	{	
		GuiManager::getInstance()->setRootElement(m_guiFrame);
	}
	m_worldManager->tick(nFps);
	m_shadowMapManager->tick(nFps);
	m_renderer->render();
}

void WorldState::toggleMouse()
{
	m_bMouseHide = !m_bMouseHide;
	if (m_bMouseHide)
	{
		glutSetCursor(GLUT_CURSOR_NONE);
	}
	else
	{
		glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
	}
}

bool WorldState::mouseHidden()
{
	return m_bMouseHide;
}

ChunkManager *WorldState::getChunkManager()
{
	return m_chunkManager;
}
	
PhysicsManager *WorldState::getPhysicsManager()
{
	return m_physicsManager;
}
	
WorldManager *WorldState::getWorldManager()
{
	return m_worldManager;
}
	
WorldRenderer *WorldState::getRenderer()
{
	return m_renderer;
}
	
ShadowMapManager *WorldState::getShadowMapManager()
{
	return m_shadowMapManager;
}
	
TileManager *WorldState::getTileManager()
{
	return m_tileManager;
}