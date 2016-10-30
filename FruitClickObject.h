#ifndef FRUITCLICKOBJECT_H
#define FRUITCLICKOBJECT_H

#include "ClickObject.h"
#include "Tree.h"

/*
 * Author: wcrane
 * Date: 5/14/2013
 *
 * Handles onClick events when the user clicks on a fruit on a tree
 */
class FruitClickObject : public ClickObject
{
private:
	Tree *m_parentTree;
	int m_nFruitIndex;

public:
	FruitClickObject(Tree *parentTree, int nFruitIndex);

	void onClick();
};

#endif