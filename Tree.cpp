#include "Tree.h"
#include "WorldState.h"

Tree::Tree() : Tile() {
	for (int i=0; i<3; i++) {
		fruit[i] = new Object();
		fruitTransforms[i] = new Transformable();
	}
	fruitTransforms[0]->setTranslate(0.8,2.0,0.3);
	fruitTransforms[1]->setTranslate(0.0,2.0,-1.0);
	fruitTransforms[2]->setTranslate(-0.8,2.0,0.3);
}

void Tree::drawExtra(std::string shader) {
	WorldState *worldState = (WorldState *)Root::GAMESTATE;
	for (int i=0; i<3; i++) {
		Root::ModelviewMatrix.push(Root::ModelviewMatrix.top());
		Root::NormalMatrix.push(Root::NormalMatrix.top());
			std::string sFruitTile = fruit[i]->getWorldComponent()->getWorldTile();
			Tile *fruitTile = worldState->getTileManager()->getTile(sFruitTile);
			fruitTransforms[i]->transformToMatrix(&Root::ModelviewMatrix.top());
			fruitTransforms[i]->transformToMatrix(&Root::NormalMatrix.top());
			fruitTile->drawTile(shader);
		Root::ModelviewMatrix.pop();
		Root::NormalMatrix.pop();
	}
}