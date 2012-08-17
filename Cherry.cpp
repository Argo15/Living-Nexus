#include "Cherry.h"
#include "WorldCherryComponent.h"

Cherry::Cherry() : Fruit()
{
	worldComponent = new WorldCherryComponent();
}