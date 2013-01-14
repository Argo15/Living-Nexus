#ifndef MATERIALMANAGER_H
#define MATERIALMANAGER_H

#include <string>
#include <map>
#include "Material.h"
using namespace std;

class MaterialManager {
private:
	static MaterialManager *m_pInstance;
	map<string,Material *> materials;
	string getSafeName(string baseName);

	MaterialManager();
public:
	static MaterialManager *getInstance();

    void Initialize();
	void LoadMaterial(string filename);
	string AddMaterialSafe(Material *material);
	bool hasMaterial(string name);
	string renameMaterial(string currentName, string newName);
	void DeleteMaterial(string name);
	void DeleteAllMaterials();

	void SaveAllMaterials();

	void UseMaterial(string name);
	Material *getMaterial(string name);
	map<string,Material *> *getMaterials();
};

#endif