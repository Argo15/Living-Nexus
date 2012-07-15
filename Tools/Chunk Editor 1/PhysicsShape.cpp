#include "PhysicsShape.h"
#include "ArgoModelManager.h"
#include "ArgoMaterialManager.h"

PhysicsShape::PhysicsShape(PhysicsShapeType type, QString name)
	: ArgoActor()
{
	setName(new QString(name));
	this->type=type;
	setMaterial(ArgoMaterialManager::Instance()->getMaterial("Physics")->getName());
	switch(type) {
		case BOX:
			setModel(ArgoModelManager::Instance()->getModel("Cube")->getName());
			break;
		case CYLINDER:
			setModel(ArgoModelManager::Instance()->getModel("Cylinder")->getName());
			break;
		case SPHERE:
			setModel(ArgoModelManager::Instance()->getModel("Sphere")->getName());
			break;
	}
}