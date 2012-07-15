#include "Object.h"

Object::Object() {
	worldComponent = new WorldComponent();
	inventoryComponent = new InventoryComponent();
	groundComponent = new GroundComponent();
}