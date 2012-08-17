#include "Orange.h"
#include "WorldOrangeComponent.h"

Orange::Orange() : Fruit()
{
	worldComponent = new WorldOrangeComponent();
}