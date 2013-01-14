#include "Model.h"

int Model::getNumTriangles()
{
	return numTriangles;
}

float *Model::getCenter() 
{
	return center;
}

float Model::getRadius() 
{
	return radius;
}