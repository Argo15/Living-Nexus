#include "User.h"
#include "Config.h"

User::User(std::string name) 
{
	username = name;
	int numObjects = Config::getInstance()->getFieldInt("INVENTORY_SIZE");
	objects = new Object*[numObjects];
	for (int i = 0; i < numObjects; i++) 
	{
		objects[i] = new Object();
	}
}

User::~User() 
{

}

std::string User::getName() 
{ 
	return username; 
}