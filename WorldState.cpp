#include "WorldState.h"
#include "Matrix.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "InventoryGui.h"
#include "GuiManager.h"

WorldState *WorldState::getInstance()
{
	return (WorldState *) GameState::GAMESTATE;
}

WorldState::WorldState(const char *sFilename)
{ 
	m_physicsManager = new PhysicsManager();
	m_renderer = new WorldRenderer();
	m_renderer->init();
	glutSetCursor(GLUT_CURSOR_NONE);

	m_worldManager = new WorldManager();
	if (sFilename == 0)
	{
		m_worldManager->generateNewWorld(m_physicsManager);
	}
	else
	{
		m_worldManager->loadWorld(string(sFilename));
	}

	m_shadowMapManager = new ShadowMapManager();

	m_bMouseHide = true;
	m_bMovementEnabled = true;

	m_worldHud = new WorldHud();
	m_inventoryGui = new InventoryGui();
	m_inventoryFrame = new SquareFrame();
	m_inventoryFrame->addElement(m_inventoryGui);
}

WorldState::~WorldState()
{

}

void WorldState::resize(int nWidth, int nHeight)
{
	m_renderer->resize(nWidth, nHeight);
	m_inventoryFrame->initialize(m_renderer->getView());
	m_worldHud->initialize(m_renderer->getView());
}

void WorldState::tick(int nFps)
{
	if (gInputManager->isKeyDownOnce((int)'t'))
	{
		toggleMouse();
	}
	// Open inventory
	if (gInputManager->isKeyDownOnce((int)'f'))
	{
		toggleInventory();
	}
	if (m_bMovementEnabled)
	{
		m_physicsManager->tick(nFps);
		gGuiManager->setRootElement(m_worldHud);
	}
	m_worldManager->tick(nFps);
	m_shadowMapManager->tick(nFps);
	m_renderer->render();
}

void WorldState::toggleInventory()
{
	m_bMovementEnabled = !m_bMovementEnabled;
	toggleMouse();
	if (gGuiManager->getRootElement() == m_inventoryFrame)
	{
		gGuiManager->setRootElement(m_worldHud);
	}
	else
	{
		m_inventoryGui->init();
		gGuiManager->setRootElement(m_inventoryFrame);
	}
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