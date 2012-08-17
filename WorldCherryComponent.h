#ifndef WORLDCHERRYCOMPONENT_H
#define WORLDCHERRYCOMPONENT_H

#include "WorldFruitComponent.h"

class WorldCherryComponent : public WorldFruitComponent {
public:
	std::string getWorldTile() {return "Cherry";}
};

#endif