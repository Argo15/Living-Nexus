#ifndef GROUNDCOMPONENT_H
#define GROUNDCOMPONENT_H

#include <string>

/*
 * author wcrane
 * date 7/14/2012
 * Holds an object's data for when it's laying on the ground. 
 * For example the tile being drawn.
 */
class GroundComponent {
public:
	GroundComponent() {}
	std::string getGroundTile();
};

#endif