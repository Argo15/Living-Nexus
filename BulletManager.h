#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H

#include "btBulletDynamicsCommon.h"
#include "PhysicsShape.h"

class BulletManager {
private:
	btDiscreteDynamicsWorld* dynamicsWorld;
	btRigidBody *playerBody;

public:
	BulletManager();
	~BulletManager() {}

	void tick(int fps);
	void addPhysicsShape(PhysicsShape *shape);
	void clearDynamicsWorld();
	void createPlayerBody();
	void updateDynamicsWorld(float speed);
};

#endif