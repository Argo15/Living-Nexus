#ifndef CLICKOBJECT_H
#define CLICKOBJECT_H

#include <string>
#include "Matrix.h"
#include "Tile.h"
#include "WorldState.h"

/*
 * Author: wcrane
 * Date: 5/14/2013
 *
 * Interface of an object that will be queued up in the ClickManager. 
 * Responds to mouse clicks on the 3D object.
 */
class ClickObject 
{
protected:
	Tile *m_tile;
	glm::mat4 m_transformMat;

public:
	ClickObject(Tile *tile = 0, glm::mat4 transformMat = glm::mat4(1.0f));

	Tile *getTile();
	glm::mat4 getTransform();
	virtual void onClick();
};

#endif