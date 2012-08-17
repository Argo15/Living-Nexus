#include "Apple.h"
#include "WorldAppleComponent.h"

Apple::Apple() : Fruit()
{
	worldComponent = new WorldAppleComponent();
}