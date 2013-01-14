#include "ModelManager.h"
#include<stdio.h>
#include<cstdlib>
#include<iostream>
#include<string.h>
#include<fstream>
#include "dirent.h"
#include "Logger.h"

ModelManager* ModelManager::m_pInstance = 0;

ModelManager::ModelManager()
{
}

ModelManager *ModelManager::getInstance() 
{
	if (m_pInstance == 0) 
	{
		m_pInstance = new ModelManager();
	}
	return m_pInstance;
}

void ModelManager::Initialize()
{
	Logging::GRAPHICS->info("Loading Models");
	DIR *pDIR;
	struct dirent *entry;
	if( pDIR=opendir("./Data/Models") )
	{
		while(entry = readdir(pDIR))
		{
			if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 )
			{
				LoadModel(string("./Data/Models/") + entry->d_name);
			}
		}
		closedir(pDIR);
	}
	Logging::GRAPHICS->info("Done Loading Models");
}

void ModelManager::LoadModel(string filename)
{
	Model *model = new AObjModel();
	if (model->load(filename)) 
	{
		int start_pos = filename.rfind("/")+1;
		int end_pos = filename.rfind(".");
		string name = filename.substr(start_pos,end_pos-start_pos);
		model->setName(name);
		models[name]=model;
	} 
	else 
	{
		Logging::GRAPHICS->error("Model failed to load: " + filename);
	}
}

void ModelManager::DrawModel(string name)
{
	models[name]->draw();
}

void ModelManager::DrawModelGeometry(string name)
{
	models[name]->drawGeometry();
}

void ModelManager::DeleteModel(string name)
{
	if (models.find(name) == models.end())
	{
		models[name]->remove();
		delete models[name];
		models.erase(name);
	}
}

void ModelManager::DeleteAllModels()
{
	models.clear();
}

Model *ModelManager::getModel(string name)
{ 
	return models[name]; 
}

map<string,Model *> *ModelManager::getModels() 
{
	return &models;
}	