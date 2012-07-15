#include "SaveChunk.h"
#include "ArgoSceneManager.h"
#include "ArgoObject.h"

void SaveChunk::saveChunk(const char *filename)
{
	QMap<QString,ArgoObject *> *objectMap = ArgoSceneManager::Instance()->getObjects();
	QMap<QString,ArgoObject *>::iterator iobject;
	numActors = objectMap->size();
	actors = new SaveActor[numActors];
	int i=0;
	for (iobject = objectMap->begin(); iobject != objectMap->end(); ++iobject) {
		ArgoObject *object = iobject.value();
		strcpy(actors[i].name,qPrintable(*object->getName()));
		strcpy(actors[i].material,qPrintable(*object->getMaterial()));
		strcpy(actors[i].model,qPrintable(*object->getModel()));
		for (int j=0; j<3; j++) {
			actors[i].rotation[j] = object->getRotate()[j];
			actors[i].scale[j] = object->getScale()[j];
			actors[i].translation[j] = object->getTranslate()[j];
		}
		actors[i].rotation[3] = object->getRotate()[3];
		i++;
	}

	for (int i=0; i<10; i++) {
		for (int j=0; j<10; j++) {
			tileModes[i][j] = ArgoSceneManager::Instance()->getChunk()->tileMode[i][j];
		}
	}

	QMap<QString,PhysicsShape *> *physicsMap = ArgoSceneManager::Instance()->getPhysicsShapes();
	QMap<QString,PhysicsShape *>::iterator iphysics;
	numPhysics = physicsMap->size();
	physics = new SavePhysics[numPhysics];
	i=0;
	for (iphysics = physicsMap->begin(); iphysics != physicsMap->end(); ++iphysics) {
		PhysicsShape *object = iphysics.value();
		for (int j=0; j<3; j++) {
			physics[i].rotation[j] = object->getRotate()[j];
			physics[i].scale[j] = object->getScale()[j];
			physics[i].translation[j] = object->getTranslate()[j];
		}
		physics[i].rotation[3] = object->getRotate()[3];
		physics[i].physicsType = object->getType();
		i++;
	}

	ofstream file(filename, ios::out|ios::binary|ios::ate);
	if (file.is_open())
	{ 
		file.write((char*)&numActors,sizeof(numActors));
		file.write((char*)actors,sizeof(SaveActor)*numActors);
		file.write((char*)&numPhysics,sizeof(numPhysics));
		file.write((char*)physics,sizeof(SavePhysics)*numPhysics);
		file.write((char*)tileModes,sizeof(tileModes));

		file.close();
	}
}