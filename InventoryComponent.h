#ifndef INVENTORYCOMPONENT_H
#define INVENTORYCOMPONENT_H

#include <string>

/*
 * author wcrane
 * date 7/14/2012
 * Holds an object's data for when it's in the user's inventory. 
 * For example the actions take when you use the object, or what texture is used in the inventory.
 */
class InventoryComponent {
public:
	InventoryComponent() {}
	virtual std::string getInventoryTexture();
};

#endif