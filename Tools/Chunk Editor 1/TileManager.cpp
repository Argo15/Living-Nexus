#include "TileManager.h"
#include "ArgoMaterialManager.h"
#include "ArgoModelManager.h"
#include "SaveTile.h"

TileManager* TileManager::pInstance = 0;

TileManager::TileManager()
{
	
}

TileManager* TileManager::Instance()
{
	return pInstance;
}

void TileManager::Initialize()
{
	pInstance = new TileManager;

}

void TileManager::LoadTile(const char *filename)
{
	ifstream file(filename, ios::in|ios::binary|ios::ate);
	if (file.is_open())
	{
		file.seekg (0, ios::beg);
		int numActors = 0;
		SaveTile::SaveActor *actors;
		file.read((char*)&numActors,sizeof(numActors));
		actors = new SaveTile::SaveActor[numActors];
		file.read((char*)actors,sizeof(SaveTile::SaveActor)*numActors);

		QString location(filename);
		QStringList fields = location.split('/');
		QString right = fields.takeLast();
		fields = right.split('.');
		Tile *newTile = new Tile(fields.takeFirst());

		for (int i=0; i<numActors; i++) {
			ArgoActor *newActor = new ArgoActor(new QString(actors[i].name),
				ArgoModelManager::Instance()->getModel(QString(actors[i].model))->getName(),
				ArgoMaterialManager::Instance()->getMaterial(QString(actors[i].material))->getName());
			newActor->setTranslate(actors[i].translation[0],actors[i].translation[1],actors[i].translation[2]);
			newActor->setRotate(ArgoQuaternion(actors[i].rotation[0],actors[i].rotation[1],actors[i].rotation[2],actors[i].rotation[3]));
			newActor->setScale(actors[i].scale[0],actors[i].scale[1],actors[i].scale[2]);
			newTile->addActor(newActor);
		}
		
		tiles.push_back(newTile);

		file.close();
	}
}

Tile *TileManager::getTile(QString name)
{
	for (int i=0; i<tiles.size(); i++) {
		if (tiles[i]->getName() == name)
			return tiles[i];
	}
	return 0;
}