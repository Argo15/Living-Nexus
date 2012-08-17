#include "Pear.h"
#include "WorldPearComponent.h"

Pear::Pear() : Fruit()
{
	worldComponent = new WorldPearComponent();
}