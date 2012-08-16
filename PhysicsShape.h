#ifndef PHYSICSSHAPE_H
#define PHYSICSSHAPE_H

#include "Actor.h"
#include "btBulletDynamicsCommon.h"

enum PhysicsShapeType {BOX, CYLINDER, SPHERE};

class PhysicsShape : public Actor {
private:
	PhysicsShapeType type;

	btCollisionShape *getBoxShape();
	btCollisionShape *getSphereShape();
	btCollisionShape *getCylinderShape();
	

public:
	PhysicsShape(PhysicsShapeType type) {this->type=type;}
	~PhysicsShape() {}

	btCollisionShape *getCollisionShape();
	PhysicsShapeType getShapeType() {return type;}
	glm::mat4 matrix;
};

#endif