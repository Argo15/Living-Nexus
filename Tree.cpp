#include "Tree.h"
#include "WorldState.h"
#include "FruitFactory.h"
#include "GameState.h"
#include "MatrixManager.h"

Tree::Tree() : Tile() 
{
	int fruitType = (rand()%5);
	for (int i=0; i<3; i++) 
	{
		fruit[i] = FruitFactory::buildFruit((FruitType)fruitType);
		fruitTransforms[i] = new Transformable();
	}
	Quaternion rot;
	rot.createQuaternion(3.1414/2.0, 0, 1, 0);
	fruitTransforms[0]->setTranslate(0.8,2.0,0.3);
	fruitTransforms[1]->setTranslate(0.0,2.0,0.1);
	fruitTransforms[1]->setRotate(rot);
	fruitTransforms[2]->setTranslate(-0.8,2.0,0.3);
}

void Tree::drawExtra(std::string shader) 
{
	WorldState *worldState = (WorldState *)GameState::GAMESTATE;
	for (int i=0; i<3; i++)
	{
		if (fruit[i] != 0) 
		{
			std::string sFruitTile = fruit[i]->getWorldTile();
			Tile *fruitTile = worldState->getTileManager()->getTile(sFruitTile);
			MatrixManager::getInstance()->pushMatrix4(MODELVIEW, fruitTransforms[i]->transformToMatrix(MatrixManager::getInstance()->getMatrix4(MODELVIEW)));
			MatrixManager::getInstance()->pushMatrix3(NORMAL, fruitTransforms[i]->transformToMatrix(MatrixManager::getInstance()->getMatrix3(NORMAL)));
			fruitTile->drawTile(shader);
			MatrixManager::getInstance()->popMatrix4(MODELVIEW);
			MatrixManager::getInstance()->popMatrix3(NORMAL);
		}
	}
}