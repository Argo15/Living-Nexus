#ifndef WORLDPEARCOMPONENT_H
#define WORLDPEARCOMPONENT_H

#include "WorldFruitComponent.h"

class WorldPearComponent : public WorldFruitComponent {
public:
	std::string getWorldTile() {return "Pear";}
};

#endif