#ifndef WORLDCOMPONENT_H
#define WORLDCOMPONENT_H

#include <string>

/*
 * author wcrane
 * date 7/14/2012
 * Holds an object's data for when it's in the world, such as it's tile and click responses.
 */
class WorldComponent {
public:
	WorldComponent() {}
	std::string getWorldTile();
};

#endif