#include "InventoryComponent.h"

static std::string S_DEFAULT_INVENTORY_TEXTURE = "cobble";

std::string InventoryComponent::getInventoryTexture() {
	return S_DEFAULT_INVENTORY_TEXTURE;
}