#ifndef ARGOSCENEMANAGER_H
#define ARGOSCENEMANAGER_H

#include <QGLWidget>
#include <QtGui>
#include "ArgoObject.h"
#include "ArgoMaterialManager.h"
#include "ArgoFrustum.h"
#include "Transformer.h"
#include "GLSLProgram.h"
#include "ArgoDirectLight.h"
#include "ArgoPointLight.h"
#include "LightEditor.h"
#include "DockedActorEditor.h"
#include "ArgoPort.h"
#include "Chunk.h"
#include "PhysicsShape.h"

class ArgoPointLight;

class ArgoSceneManager {
public:
	static ArgoSceneManager* Instance();
    static void Initialize();
	void AddObject(ArgoObject *object);
	void AddPointLight(ArgoPointLight *light);
	void AddPhysicsShape(PhysicsShape *physicsShape);
	void DrawScene(ArgoFrustum *frustum, GLSLProgram *program = 0);
	void RenameObject(QString oldName, QString newName);
	void RenamePointLight(QString oldName, QString newName);
	void DeleteActor(QString name);
	void DeleteScene();

	void copySelected();

	void setSelected(QString *selected);
	QString *getSelected() {return selectedActor;}
	void deleteSelected();

	void setDirectLight(ArgoDirectLight *dLight);
	ArgoDirectLight *getDirectLight() {return directLight;}

	void setEntrance(ArgoPort *entrance);
	ArgoPort *getEntrance() {return entrance;}

	void setExit(ArgoPort *exit);
	ArgoPort *getExit() {return exit;}

	ArgoObject *getObject(QString name) {if(objects.contains(name)) return objects[name]; else return 0;}
	QMap<QString,ArgoObject *> *getObjects() {return &objects;}
	ArgoPointLight *getPointLight(QString name) {if(pointLights.contains(name)) return pointLights[name]; else return 0;}
	QMap<QString,ArgoPointLight *> *getPointLights() {return &pointLights;}
	PhysicsShape *getPhysicsShape(QString name) {if(physicsShapes.contains(name)) return physicsShapes[name]; else return 0;}
	QMap<QString,PhysicsShape *> *getPhysicsShapes() {return &physicsShapes;}
	ArgoActor *getActor(QString name) {if(actors.contains(name)) return actors[name]; else return 0;}
	QMap<QString,ArgoActor *> *getActors() {return &actors;}

	Chunk *getChunk() {return chunk;}
	
	void RenameActor(QString oldName, QString newName);
	void RenameActorSmart(QString oldName, QString newName);

private:
    QMap<QString,ArgoObject *> objects;
	ArgoDirectLight *directLight;
	QMap<QString,ArgoPointLight *> pointLights; 
	QMap<QString,PhysicsShape *> physicsShapes; 
	QMap<QString,ArgoActor *> actors; 
	ArgoPort *entrance;
	ArgoPort *exit;
	QString *selectedActor;
	Chunk *chunk;

	ArgoSceneManager();
    static ArgoSceneManager* pInstance;
	
	void AddActor(ArgoActor *actor);
};

#endif