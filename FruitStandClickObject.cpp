#include "FruitStandClickObject.h"
#include "Logger.h"

FruitStandClickObject::FruitStandClickObject(Tile *tile, glm::mat4 transformMat) : ClickObject(tile, transformMat)
{
}

void FruitStandClickObject::onClick()
{
	Logging::GAME->info("I was clicked: " + *m_tile->getName());
	WorldState::getInstance()->getInventory()->setOptionsType(SHOP_OPTIONS);
	WorldState::getInstance()->toggleInventory();
}