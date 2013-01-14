#ifndef ENTITY_H
#define ENTITY_H

#include <string>
using namespace std;

class Entity
{
protected:
	string *name;

public:
	Entity(string *name = 0);

	string *getName();
	void setName(string newName);
};

#endif