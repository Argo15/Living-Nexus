#ifndef FRUITSTANDCLICKOBJECT_H
#define FRUITSTANDCLICKOBJECT_H

#include <string>
#include "Matrix.h"
#include "Tile.h"
#include "WorldState.h"
#include "ClickObject.h"

/*
 * Author: wcrane
 * Date: 6/2/2013
 *
 * Mouse click handler for the fruit stand
 */
class FruitStandClickObject : public ClickObject
{
public:
	FruitStandClickObject(Tile *tile = 0, glm::mat4 transformMat = glm::mat4(1.0f));

	virtual void onClick();
};

#endif