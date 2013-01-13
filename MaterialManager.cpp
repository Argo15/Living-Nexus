#include "MaterialManager.h"
#include<stdio.h>
#include<cstdlib>
#include<iostream>
#include<string.h>
#include<fstream>
#include "dirent.h"
#include "Logger.h"

MaterialManager* MaterialManager::m_pInstance = 0;

MaterialManager::MaterialManager()
{
	
}

MaterialManager *MaterialManager::getInstance() 
{
	if (m_pInstance == 0) 
	{
		m_pInstance = new MaterialManager();
	}
	return m_pInstance;
}

void MaterialManager::Initialize()
{
	Logging::GRAPHICS->info("Loading Materials");
	DIR *pDIR;
	struct dirent *entry;
	if( pDIR=opendir("./Data/Materials") ){
		while(entry = readdir(pDIR)){
			if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 )
				LoadMaterial(string("./Data/Materials/") + entry->d_name);
		}
		closedir(pDIR);
	}
	Logging::GRAPHICS->info("Done Loading Materials");
}

void MaterialManager::LoadMaterial(string filename)
{
	Material *newMaterial = new Material();
	if (newMaterial->loadMaterial(filename.c_str())) 
	{
		string *name = newMaterial->getName();
		materials[*name] = newMaterial;
	} 
	else 
	{
		Logging::GRAPHICS->error("Material failed to load: " + filename);
	}
}

/* 
 * returns a string that is not currently being used
 */
string MaterialManager::getSafeName(string baseName)
{
	if (!hasMaterial(baseName))
	{
		return baseName;
	} 
	else
	{
		int nNum = 1;
		while (true)
		{
			char buff[10];
			itoa(nNum, buff, 10);
			string sNum = string(buff);
			string newName = baseName + sNum;
			if (!hasMaterial(newName)) 
			{
				return newName;
			}
			nNum++;
		}
	}
}

/* returns the name of the material */
string MaterialManager::AddMaterialSafe(Material *material)
{
	string matName = getSafeName(*(material->getName()));
	material->setName(matName);
	materials[matName] = material;
	return matName;
}

bool MaterialManager::hasMaterial(string name)
{
	if (materials.find(name) != materials.end()) 
	{
		return true;
	}
	return false;
}

string MaterialManager::renameMaterial(string currentName, string newName) 
{
	Material *mat = materials[currentName];
	materials.erase(currentName);
	newName = getSafeName(newName);
	mat->setName(newName);
	materials[newName] = mat;
	return newName;
}

void MaterialManager::DeleteMaterial(string name)
{
	if (materials.find(name) != materials.end()) 
	{
		delete materials[name];
		materials.erase(name);
	}
}

void MaterialManager::DeleteAllMaterials()
{
	materials.clear();
}

void MaterialManager::SaveAllMaterials()
{
	for (std::map<std::string, Material *>::iterator it = materials.begin(); it != materials.end(); it++)
	{
		Material *mat = (*it).second;
		string filename = "Data/Materials/" + (*it).first + ".amtl";
		mat->saveMaterial(filename.c_str());
	}
}