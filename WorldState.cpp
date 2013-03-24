#include "WorldState.h"
#include "Matrix.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "HorizontalLayout.h"
#include "VerticalLayout.h"
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

	m_inventoryGui = new HorizontalLayout();
	GuiElement *leftElement = new GuiElement();
	leftElement->setWidth(0.3);
	leftElement->setColor(1.0,0,0,0.5);
	GuiElement *middleElement = new GuiElement();
	middleElement->setWidth(0.4);
	middleElement->setHeight(0.5);
	middleElement->setColor(0,0,1.0,0.5);

	Layout *rightLayout = new VerticalLayout();
	rightLayout->setWidth(0.3);
	rightLayout->setPadding(0.05);
	GuiElement *topElement = new GuiElement();
	topElement->setHeight(0.5);
	topElement->setColor(0,1.0,0,0.5);
	GuiElement *bottomElement = new GuiElement();
	bottomElement->setHeight(0.5);
	bottomElement->setColor(1.0,0,1.0,0.5);
	bottomElement->setPadding(0, 0, 0, 0.1);

	rightLayout->addElement(bottomElement);
	rightLayout->addElement(topElement);

	m_inventoryGui->addElement(leftElement);
	m_inventoryGui->addElement(middleElement);
	m_inventoryGui->addElement(rightLayout);
}

WorldState::~WorldState()
{

}

void WorldState::resize(int nWidth, int nHeight)
{
	m_renderer->resize(nWidth, nHeight);
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
		toggleMouse();
		m_bMovementEnabled = !m_bMovementEnabled;
	}
	if (m_bMovementEnabled)
	{
		GuiManager::getInstance()->setRootElement(0);
		m_physicsManager->tick(nFps);
	}
	else
	{	
		GuiManager::getInstance()->setRootElement(m_inventoryGui);
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