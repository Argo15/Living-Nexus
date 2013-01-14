#ifndef ACTOR_H
#define ACTOR_H

#include <math.h>
#include "Model.h"
#include "Matrix.h"
#include "ModelManager.h"
#include "Transformable.h"
#include "GLSLProgram.h"

class Actor : public Entity, public Transformable 
{
private:
	string *model;
	string *material;
	
public:
	Actor(string *model = 0, string *material = 0);

	void drawActor(string shader);
	float getScaledRadius();
	void setModel(string *model);
	string *getModel();
	void setMaterial(string *material);
	string *getMaterial();

};

#endif