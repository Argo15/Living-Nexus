#ifndef FRUIT_H
#define FRUIT_H

#include <string>
#include "Object.h"

/*
 * Author: wcrane
 * Date: 1/6/2013
 * Fruit object created by FruitFactory, appears on trees.
 */
class Fruit : public Object
{
public:
	Fruit(string sName, string sWorldTile, string sInventoryTexture, string sGroundTile);
};

#endif