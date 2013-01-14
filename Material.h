#ifndef MATERIAL_H
#define MATERIAL_H

#include <iostream>
#include <fstream>
#include "Entity.h"
#include "TextureManager.h"
#include "Matrix.h"
#include "ShaderManager.h"
using namespace std;

struct SaveMat 
{
	float color[3];
	float emission[3];
	float specular;
	int shininess;

	float texOffset[2];
	float texScale[2];
	float texRotate;

	char name[100];
	char textureName[100];
	char normalName[100];

	bool normalEnabled;
};

class Material : public Entity
{
private:
	float color[3];
	float emission[3];
	float specular;
	int shininess;

	float texOffset[2];
	float texScale[2];
	float texRotate;

	string *textureName;
	string *normalName;

	bool normalEnabled;
public:
	Material();
	Material(Material *copyMaterial);

	void use();
	void sendToShader(string shader);

	bool loadMaterial(const char* filename);
	void saveMaterial(const char* filename);

	void setColor(float r, float g, float b);
	void setEmission(float r, float g, float b);
	void setSpecular(float i);
	void setShine(int shine);
	void setTexOffset(float x, float y);
	void setUTexOffset(float value);
	void setVTexOffset(float value);
	void setTexScale(float x, float y);
	void setUTexScale(float value);
	void setVTexScale(float value);
	void setTexRotate(float rotate);
	float *getColor();
	float *getEmission();
	float getSpecular();
	int getShine();
	float *getTexOffset();
	float *getTexScale();
	float getTexRotate();
	void setTexture(string *newTextureName);
	string *getTexture();
	void setNormal(string *newNormalName);
	string *getNormal();
	void enableNormal(bool enabled);
	bool normalsEnabled();
};

#endif