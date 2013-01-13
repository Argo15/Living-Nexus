#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include <string>
#include <map>
#include "AObjModel.h"
using namespace std;

class ModelManager
{
private:
	static ModelManager *m_pInstance;
	map<string,Model *> models;

	ModelManager();
public:
	static ModelManager *getInstance();

    void Initialize();
	void LoadModel(string filename);
	void DrawModel(string name);
	void DrawModelGeometry(string name);
	void DeleteModel(string name);
	void DeleteAllModels();

	Model *getModel(string name)
	{ 
		return models[name]; 
	}
	map<string,Model *> *getModels() 
	{
		return &models;
	}		
};

#endif