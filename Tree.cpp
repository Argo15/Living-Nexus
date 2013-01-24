#include "Tree.h"
#include "WorldState.h"
#include "FruitFactory.h"
#include "GameState.h"
#include "MatrixManager.h"

Tree::Tree() : Tile() 
{
	int nFruitType = (rand()%5);
	for (int i=0; i<3; i++) 
	{
		m_fruit[i] = FruitFactory::buildFruit((FruitType)nFruitType);
		m_fruitTransforms[i] = new Transformable();
	}
	Quaternion rot;
	rot.createQuaternion(3.1414/2.0, 0, 1, 0);
	m_fruitTransforms[0]->setTranslate(0.8,2.0,0.3);
	m_fruitTransforms[1]->setTranslate(0.0,2.0,0.1);
	m_fruitTransforms[1]->setRotate(rot);
	m_fruitTransforms[2]->setTranslate(-0.8,2.0,0.3);
}

void Tree::drawExtra(std::string sShader) 
{
	WorldState *worldState = (WorldState *)GameState::GAMESTATE;
	for (int i=0; i<3; i++)
	{
		if (m_fruit[i] != 0) 
		{
			std::string sFruitTile = m_fruit[i]->getWorldTile();
			Tile *fruitTile = worldState->getTileManager()->getTile(sFruitTile);
			MatrixManager::getInstance()->pushMatrix4(MODELVIEW, m_fruitTransforms[i]->transformToMatrix(MatrixManager::getInstance()->getMatrix4(MODELVIEW)));
			MatrixManager::getInstance()->pushMatrix3(NORMAL, m_fruitTransforms[i]->transformToMatrix(MatrixManager::getInstance()->getMatrix3(NORMAL)));
			fruitTile->drawTile(sShader);
			MatrixManager::getInstance()->popMatrix4(MODELVIEW);
			MatrixManager::getInstance()->popMatrix3(NORMAL);
		}
	}
}