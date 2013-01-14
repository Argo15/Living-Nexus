#include "Actor.h"
#include "MatrixManager.h"
#include "ShaderManager.h"
#include "MaterialManager.h"

Actor::Actor(string *model, string *material) : Transformable()
{
	this->model = model;
	this->material = material;
	this->name=name;
}

void Actor::drawActor(string shader)
{
	GLSLProgram *glslProgram = ShaderManager::getInstance()->getShader(shader);
	glslProgram->sendUniform("modelviewMatrix", &MatrixManager::getInstance()->getMatrix4(MODELVIEW)[0][0]);
	if (shader == "Basic" || shader == "GBuffer") 
	{
		glslProgram->sendUniform("normalMatrix", &MatrixManager::getInstance()->getMatrix3(NORMAL)[0][0],false,3);
		MaterialManager::getInstance()->getMaterial(*material)->sendToShader(shader);
	}
	ModelManager::getInstance()->getModel(*model)->draw();
}

float Actor::getScaledRadius()
{
	return ModelManager::getInstance()->getModel(*model)->getRadius()*max(max(scale[0],scale[1]),scale[2]);
}

void Actor::setModel(string *model) 
{
	this->model = model;
}

string *Actor::getModel() 
{
	return model;
}

void Actor::setMaterial(string *material) 
{
	this->material = material;
}

string *Actor::getMaterial() 
{
	return material;
}