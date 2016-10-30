#include "ClickObject.h"
#include "Logger.h"

ClickObject::ClickObject(Tile *tile, glm::mat4 transformMat)
{
	m_tile = tile;
	m_transformMat = transformMat;
}

Tile *ClickObject::getTile()
{
	return m_tile;
}
	
glm::mat4 ClickObject::getTransform()
{
	return m_transformMat;
}

void ClickObject::onClick()
{
}