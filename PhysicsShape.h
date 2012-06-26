#ifndef PHYSICSSHAPE_H
#define PHYSICSSHAPE_H

#include "Transformable.h"
#include "btBulletDynamicsCommon.h"

enum PhysicsShapeType {BOX, CYLINDER, SPHERE};

class PhysicsShape : public Transformable {
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