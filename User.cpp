#include "User.h"
#include "Config.h"

User::User(std::string sName) 
{
	m_sUsername = sName;
	int numObjects = Config::getInstance()->getFieldInt("INVENTORY_SIZE");
	m_objects = new Object*[numObjects];
	for (int i = 0; i < numObjects; i++) 
	{
		m_objects[i] = 0;
	}
}

User::~User() 
{

}

std::string User::getName() 
{ 
	return m_sUsername; 
}