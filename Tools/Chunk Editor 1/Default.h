#include "ArgoSceneManager.h"
#include "TileManager.h"

static void LoadDefaultPorts()
{
	ArgoModelManager::Instance()->LoadModel("Data/Models/AOBJ/Sphere.aobj");
	ArgoModelManager::Instance()->setPortModel(ArgoModelManager::Instance()->getModel("Sphere")->getName());

	ArgoMaterial *entranceMaterial = new ArgoMaterial(new QString("Entrance"));
	entranceMaterial->setTexture(ArgoTextureManager::Instance()->getWhite()->getName());
	entranceMaterial->setEmission(0.0,1.0,0.0);
	entranceMaterial->setColor(0.0,1.0,0.0);
	ArgoMaterial *exitMaterial = new ArgoMaterial(new QString("Exit"));
	exitMaterial->setTexture(ArgoTextureManager::Instance()->getWhite()->getName());
	exitMaterial->setEmission(1.0,0.0,0.0);
	exitMaterial->setColor(1.0,0.0,0.0);
	ArgoMaterialManager::Instance()->AddMaterial(entranceMaterial);
	ArgoMaterialManager::Instance()->AddMaterial(exitMaterial);
	ArgoMaterialManager::Instance()->setEntranceMaterial(entranceMaterial->getName());
	ArgoMaterialManager::Instance()->setExitMaterial(exitMaterial->getName());
}

static void LoadDefaultMaterials() 
{
	ArgoMaterial *defaultMaterial = new ArgoMaterial(new QString("Default"));
	defaultMaterial->setTexture(ArgoTextureManager::Instance()->getTexture("White")->getName());
	ArgoMaterial *lightMaterial = new ArgoMaterial(new QString("Light"));
	lightMaterial->setTexture(ArgoTextureManager::Instance()->getTexture("White")->getName());
	lightMaterial->setEmission(1.0,1.0,1.0);
	ArgoMaterialManager::Instance()->AddMaterial(defaultMaterial);
	ArgoMaterialManager::Instance()->AddMaterial(lightMaterial);
	ArgoMaterialManager::Instance()->setDefault(defaultMaterial->getName());
	ArgoMaterialManager::Instance()->setLightMaterial(lightMaterial->getName());
}

static void LoadDefaultScene()
{
	QStringList texturefilters;
    texturefilters << "*.tga";
	QStringList textures = QDir("Data/Textures/TGA/").entryList(texturefilters);
	for (int i = 0; i < textures.size(); ++i) 
          ArgoTextureManager::Instance()->LoadTexture(QString("Data/Textures/TGA/")+textures.at(i));
	ArgoTextureManager::Instance()->SetWhite(ArgoTextureManager::Instance()->getTexture("White")->getName());
	ArgoTextureManager::Instance()->getTexture("Concrete Normal")->setType("Normal");
	ArgoTextureManager::Instance()->getTexture("Test Normals")->setType("Normal");
	ArgoTextureManager::Instance()->getTexture("cobbleNormalsMap")->setType("Normal");

	QStringList modelfilters;
    modelfilters << "*.aobj";
	QStringList models = QDir("Data/Models/AOBJ/").entryList(modelfilters);
	for (int i = 0; i < models.size(); ++i) 
          ArgoModelManager::Instance()->LoadModel(QString("Data/Models/AOBJ/")+models.at(i));
	ArgoModelManager::Instance()->LoadModel("Data/Models/Light/DirectLight.aobj");
	ArgoModelManager::Instance()->LoadModel("Data/Models/Light/PointLight.aobj");
	ArgoModelManager::Instance()->setDefault(ArgoModelManager::Instance()->getModel("Cube")->getName());
	ArgoModelManager::Instance()->setPointLightModel(ArgoModelManager::Instance()->getModel("PointLight")->getName());
	ArgoModelManager::Instance()->setDirectLightModel(ArgoModelManager::Instance()->getModel("DirectLight")->getName());

	QStringList matfilters;
    matfilters << "*.amtl";
	QStringList materials = QDir("Data/Materials/").entryList(matfilters);
	for (int i = 0; i < materials.size(); ++i) 
          ArgoMaterialManager::Instance()->LoadMaterial(qPrintable(QString("Data/Materials/")+materials.at(i)));
	ArgoMaterialManager::Instance()->setDefault(ArgoMaterialManager::Instance()->getMaterial("Default")->getName());
	ArgoMaterialManager::Instance()->setLightMaterial(ArgoMaterialManager::Instance()->getMaterial("Light")->getName());

	QString *dLightStr = new QString("Direct Light");
	ArgoDirectLight *dLight = new ArgoDirectLight(dLightStr);
	dLight->setMaterial(ArgoMaterialManager::Instance()->getLightMaterial()->getName());
	dLight->setModel(ArgoModelManager::Instance()->getModel("DirectLight")->getName());
	dLight->setTranslate(0.0,1.3,0.0);
	dLight->setScale(0.2,0.4,0.2);
	ArgoSceneManager::Instance()->setDirectLight(dLight);

	QStringList tilefilters;
    tilefilters << "*.atl";
	QStringList tiles = QDir("Data/Tiles/").entryList(tilefilters);
	for (int i = 0; i < tiles.size(); ++i) 
          TileManager::Instance()->LoadTile(qPrintable(QString("Data/Tiles/")+tiles.at(i)));
}