#ifndef PHYSICSSHAPE_H
#define PHYSICSSHAPE_H

#include "ArgoActor.h"

enum PhysicsShapeType {BOX, CYLINDER, SPHERE};

class PhysicsShape : public ArgoActor {
private:
	PhysicsShapeType type;
public:
	PhysicsShape(PhysicsShapeType type, QString name);
	~PhysicsShape() {}

	PhysicsShapeType getType() {return type;}
	virtual bool isPhysics() {return true;}
};

#endif