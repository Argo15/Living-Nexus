#include "Tree.h"
#include "WorldState.h"
#include "FruitFactory.h"
#include "GameState.h"
#include "MatrixManager.h"
#include "ClickManager.h"
#include "FruitClickObject.h"

Tree::Tree() : Tile() 
{
	int nFruitType = (rand()%5);
	for (int i=0; i<3; i++) 
	{
		m_fruit[i] = FruitFactory::buildFruit((FruitType)nFruitType);
		m_fruitTransforms[i] = new Transformable();
	}
	Quaternion rot;
	rot.createQuaternion(3.1414f/2.0f, 0, 1.0f, 0);
	m_fruitTransforms[0]->setTranslate(0.8f,2.0f,0.3f);
	m_fruitTransforms[1]->setTranslate(0.0f,2.0f,0.1f);
	m_fruitTransforms[1]->setRotate(rot);
	m_fruitTransforms[2]->setTranslate(-0.8f,2.0f,0.3f);
}

void Tree::drawExtra(std::string sShader) 
{
	WorldState *worldState = (WorldState *)GameState::GAMESTATE;
	for (int i=0; i<3; i++)
	{
		if (m_fruit[i] != 0) 
		{
			std::string sFruitTile = m_fruit[i]->getWorldTile();
			Tile *fruitTile = gTileManager->getTile(sFruitTile);
			gMatrixManager->pushMatrix4(MODELVIEW, m_fruitTransforms[i]->transformToMatrix(gMatrixManager->getMatrix4(MODELVIEW)));
			gMatrixManager->pushMatrix3(NORMAL, m_fruitTransforms[i]->transformToMatrix(gMatrixManager->getMatrix3(NORMAL)));
			fruitTile->drawTile(sShader);
			gMatrixManager->popMatrix4(MODELVIEW);
			gMatrixManager->popMatrix3(NORMAL);
		}
	}
}

void Tree::addFruitClickObjects(Vector3 camPos, Vector3 treePos)
{
	for (int i=0; i<3; i++)
	{
		if (m_fruit[i] != 0) 
		{
			Vector3 fruitPos = treePos + m_fruitTransforms[i]->getTranslateV();
			if ((camPos-fruitPos).length() <= 4.0f)
			{	
				gClickManager->addClickObject(new FruitClickObject(this, i));
			}
		}
	}
}

Object *Tree::getFruit(int index)
{
	return m_fruit[index];
}

void Tree::setFruit(int index, Object *fruit)
{
	m_fruit[index] = fruit;
}

Transformable *Tree::getTransform(int index)
{
	return m_fruitTransforms[index];
}