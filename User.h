#ifndef USER_H
#define USER_H

#include <string>
#include "Object.h"

/*
 * User object that holds information about a user such as inventory, money, etc.
 *
 * author wcrane
 * date 7/14/2012
 */
class User 
{
private:
	std::string m_sUsername;
	Object **m_objects;
	int m_nInventorySize;

public:
	User(std::string sName);
	~User();

	Object *getInventoryObject(int nIndex);
	int getInventorySize();
	std::string getName();
};

#endif