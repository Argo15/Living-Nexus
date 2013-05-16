#include "Object.h"

Object::Object(string sName)
{
	m_sName = sName;
}

std::string Object::getWorldTile() 
{ 
	return m_sWorldTile; 
}

void Object::setWorldTile(std::string sTile)
{
	m_sWorldTile = sTile;
}
	
std::string Object::getInventoryTexture() 
{ 
	return m_sInventoryTexture; 
}

void Object::setInventoryTexture(std::string sTexture)
{
	m_sInventoryTexture = sTexture;
}
	
std::string Object::getGroundTile() 
{ 
	return m_sGroundTile; 
}

void Object::setGroundTile(std::string sTile)
{
	m_sGroundTile = sTile;
}

string Object::getName()
{
	return m_sName;
}

void Object::setName(string sName)
{
	m_sName = sName;
}