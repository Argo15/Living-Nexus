#ifndef TREE_H
#define TREE_H

#include <string>
#include "Tile.h"
#include "Object.h"
#include "Transformable.h"

class Tree : public Tile 
{
private:
	Transformable *m_fruitTransforms[3];
	Object *m_fruit[3];

public:
	Tree();
	void drawExtra(std::string sShader);
	void addFruitClickObjects(Vector3 camPos, Vector3 treePos);

	Object *getFruit(int index);
	void setFruit(int index, Object *fruit);

	Transformable *getTransform(int index);
};

#endif