#ifndef WORLDAPPLECOMPONENT_H
#define WORLDAPPLECOMPONENT_H

#include "WorldFruitComponent.h"

class WorldAppleComponent : public WorldFruitComponent {
public:
	std::string getWorldTile() {return "Apple";}
};

#endif