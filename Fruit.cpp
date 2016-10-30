#include "Fruit.h"

Fruit::Fruit(string sName, string sWorldTile, string sInventoryTexture, string sGroundTile) : Object(sName)
{
	setWorldTile(sWorldTile);
	setInventoryTexture(sInventoryTexture);
	setGroundTile(sGroundTile);
}