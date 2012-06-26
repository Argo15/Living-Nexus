#include "PhysicsShape.h"


btCollisionShape *PhysicsShape::getBoxShape()
{
	return new btBoxShape(btVector3(scale[0],scale[1],scale[2]));
}

btCollisionShape *PhysicsShape::getSphereShape()
{
	btSphereShape *sphere = new btSphereShape(1.0);
	sphere->setLocalScaling(btVector3(scale[0],scale[1],scale[2]));
	return sphere;
}

btCollisionShape *PhysicsShape::getCylinderShape()
{
	return new btCylinderShape(btVector3(scale[0],scale[1],scale[2]));
}

btCollisionShape *PhysicsShape::getCollisionShape()
{
	switch (type)
	{
		case BOX:
			return getBoxShape();
		case CYLINDER:
			return getCylinderShape();
		case SPHERE:
			return getSphereShape();
		default:
			return 0;
	}
}