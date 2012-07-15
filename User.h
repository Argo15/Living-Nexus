#ifndef USER_H
#define USER_H

#include <string>
#include "Object.h"

/*
 * author wcrane
 * date 7/14/2012
 * User object that holds information about a user such as inventory, money, etc.
 */
class User {
private:
	std::string username;
	Object **objects;

public:
	User(std::string name);
	~User();

	std::string getName() { return username; }
};

#endif