#ifndef PHYSICSSHAPE_H
#define PHYSICSSHAPE_H

#include "btBulletDynamicsCommon.h"
#include "Actor.h"

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
	glm::mat4 matrix;
};

#endif