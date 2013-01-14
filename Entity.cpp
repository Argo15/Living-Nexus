#include "Entity.h"

Entity::Entity(string *name) 
{
	this->name = name;
}

string *Entity::getName() 
{
	return name;
}

void Entity::setName(string newName) 
{
	name = new string(newName);
}