#ifndef WORLDORANGECOMPONENT_H
#define WORLDORANGECOMPONENT_H

#include "WorldFruitComponent.h"

class WorldOrangeComponent : public WorldFruitComponent {
public:
	std::string getWorldTile() {return "Orange";}
};

#endif