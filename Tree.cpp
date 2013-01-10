#include "Tree.h"
#include "WorldState.h"
#include "FruitFactory.h"
#include "GameState.h"

Tree::Tree() : Tile() {
	int fruitType = (rand()%5);
	for (int i=0; i<3; i++) {
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

void Tree::drawExtra(std::string shader) {
	WorldState *worldState = (WorldState *)GameState::GAMESTATE;
	for (int i=0; i<3; i++) {
		if (fruit[i] != 0) {
			Root::ModelviewMatrix.push(Root::ModelviewMatrix.top());
			Root::NormalMatrix.push(Root::NormalMatrix.top());
				std::string sFruitTile = fruit[i]->getWorldTile();
				Tile *fruitTile = worldState->getTileManager()->getTile(sFruitTile);
				fruitTransforms[i]->transformToMatrix(&Root::ModelviewMatrix.top());
				fruitTransforms[i]->transformToMatrix(&Root::NormalMatrix.top());
				fruitTile->drawTile(shader);
			Root::ModelviewMatrix.pop();
			Root::NormalMatrix.pop();
		}
	}
}