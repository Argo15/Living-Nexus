#include "User.h"
#include "Config.h"
#include "Logger.h"
#include "FruitFactory.h"

User::User(std::string sName) 
{
	m_sUsername = sName;
	m_nInventorySize = Config::getInstance()->getFieldInt("INVENTORY_SIZE");
	m_objects = new Object*[m_nInventorySize];
	for (int i=0; i < m_nInventorySize; i++) 
	{
		m_objects[i] = 0;
	}
}

User::~User() 
{

}

bool User::addObject(Object *object)
{
	for (int i=0; i < m_nInventorySize; i++) 
	{
		if (m_objects[i] == 0)
		{
			m_objects[i] = object;
			return true;
		}
	}
	return false;
}

std::string User::getName() 
{ 
	return m_sUsername; 
}

Object *User::getInventoryObject(int nIndex)
{
	return m_objects[nIndex];
}

int User::getInventorySize()
{
	return m_nInventorySize;
}