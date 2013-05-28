#include "FruitClickObject.h"
#include "UserSession.h"
#include "Logger.h"

FruitClickObject::FruitClickObject(Tree *parentTree, int nFruitIndex) : ClickObject()
{
	m_parentTree = parentTree;
	m_nFruitIndex = nFruitIndex;
	WorldState *worldState = (WorldState *)GameState::GAMESTATE;
	Object *fruit = parentTree->getFruit(nFruitIndex);
	Transformable *transform = parentTree->getTransform(nFruitIndex);
	Tile *fruitTile = gTileManager->getTile(fruit->getWorldTile());

	m_tile = fruitTile;
	m_transformMat = transform->transformToMatrix(parentTree->transformToMatrix(glm::mat4(1.0f)));
}

void FruitClickObject::onClick()
{
	Object *fruit = m_parentTree->getFruit(m_nFruitIndex);
	if (gUserSession->getActiveUser()->addObject(fruit))
	{
		m_parentTree->setFruit(m_nFruitIndex, 0);
		Logging::GAME->info("Added to inventory: " + *(m_tile->getName()));
	}
	else
	{
		Logging::GAME->info("Inventory full: " + *(m_tile->getName()));
	}
}