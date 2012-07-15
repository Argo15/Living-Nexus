#ifndef OBJECT_H
#define OBJECT_H

#include "WorldComponent.h"
#include "InventoryComponent.h"
#include "GroundComponent.h"

/*
 * author wcrane
 * date 7/14/2012
 * Generic object that can be placed in your inventory, placed on the ground, or placed in the world/house as an interactive object.
 */
class Object {
private:
	WorldComponent *worldComponent;
	InventoryComponent *inventoryComponent;
	GroundComponent *groundComponent;

public:
	Object();
	WorldComponent *getWorldComponent() { return worldComponent; }
	InventoryComponent *getInventoryComponent() { return inventoryComponent; }
	GroundComponent *getGroundComponent() { return groundComponent; }
};

#endif