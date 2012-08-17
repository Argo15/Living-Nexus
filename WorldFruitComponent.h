#ifndef WORLDFRUITCOMPONENT_H
#define WORLDFRUITCOMPONENT_H

#include "WorldComponent.h"

class WorldFruitComponent : public WorldComponent {
public:
	std::string getWorldTile() {return "Orange";}
};

#endif