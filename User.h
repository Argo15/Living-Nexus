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
	std::string username;
	Object **objects;

public:
	User(std::string name);
	~User();

	std::string getName();
};

#endif