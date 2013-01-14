#include "Light.h"

void Light::setAmbient(float amt)
{
	ambient=amt;
}

void Light::setDiffuse(float amt)
{
	diffuse=amt;
}

void Light::setSpecular(float amt)
{
	specular=amt;
}

float Light::getDiffuse()
{
	return diffuse;
}

float Light::getAmbient()
{
	return ambient;
}

float Light::getSpecular() 
{
	return specular;
}

void Light::setColor(float r, float g, float b) 
{
	color[0]=r; 
	color[1]=g; 
	color[2]=b;
}

float *Light::getColor() 
{
	return color;
}

bool Light::isenabled() 
{
	return enabled;
}

void Light::setEnabled(bool enabled) 
{
	this->enabled=enabled;
}