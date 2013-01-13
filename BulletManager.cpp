#include "BulletManager.h"
#include "WorldState.h"
#include "Profiler.h"
#include "GameState.h"
#include "InputManager.h"

BulletManager::BulletManager()
{
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher = new	btCollisionDispatcher(collisionConfiguration);
	btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,overlappingPairCache,solver,collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0,-10,0));
	playerBody = 0;
}

void BulletManager::tick(int fps)
{
	if (playerBody == 0)
	{
		createPlayerBody();
	}
}

void BulletManager::addPhysicsShape(PhysicsShape *shape)
{
	btCollisionShape* bodyShape = shape->getCollisionShape();
	if (bodyShape == 0) 
	{
		return;
	}
	btTransform bodyTransform;
	bodyTransform.setIdentity();
	bodyTransform.setFromOpenGLMatrix(&shape->matrix[0][0]);
	btScalar mass(0.);
	btVector3 localInertia(0,0,0);
	btDefaultMotionState* myMotionState = new btDefaultMotionState(bodyTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,bodyShape,localInertia);
	btRigidBody *body = new btRigidBody(rbInfo);
	dynamicsWorld->addRigidBody(body);
}

void BulletManager::clearDynamicsWorld()
{
	delete dynamicsWorld;
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher = new	btCollisionDispatcher(collisionConfiguration);
	btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,overlappingPairCache,solver,collisionConfiguration);
	playerBody = 0;
}

void BulletManager::createPlayerBody()
{
	btCollisionShape* bodyShape = new btCapsuleShape(.3f,2.0f);
	WorldState *worldState = (WorldState *) GameState::GAMESTATE;
	Camera *camera = worldState->getPhysicsManager()->getWorldCameras()->getPlayerCamera();
	btTransform bodyTransform;
	bodyTransform.setIdentity();
	float *translate = camera->getEye();
	bodyTransform.setOrigin(btVector3(translate[0],translate[1]-0.79f,translate[2]));
	btScalar mass(10.);
	btVector3 localInertia(0,0,0);
	bodyShape->calculateLocalInertia(mass,localInertia);
	btDefaultMotionState* myMotionState = new btDefaultMotionState(bodyTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,bodyShape,localInertia);
	playerBody = new btRigidBody(rbInfo);
	playerBody->setAngularFactor(0);
	dynamicsWorld->addRigidBody(playerBody);
}

void BulletManager::updateDynamicsWorld(float speed)
{
	Profiler::getInstance()->startProfile("Update Dynamics World");
	// move camera
	WorldState *worldState = (WorldState *) GameState::GAMESTATE;
	WorldCamera *camera = worldState->getPhysicsManager()->getWorldCameras()->getPlayerCamera();
	float oldEye[3];
	oldEye[0] = camera->geteyeX();
	oldEye[1] = camera->geteyeY();
	oldEye[2] = camera->geteyeZ();
	if (InputManager::getInstance()->isKeyDown('w'))
	{
		camera->moveForward(speed*0.1f);
	}
	if (InputManager::getInstance()->isKeyDown('s'))
	{
		camera->moveBackward(speed*0.1f);
	}
	if (InputManager::getInstance()->isKeyDown('a'))
	{
		camera->moveLeft(speed*0.1f);
	}
	if (InputManager::getInstance()->isKeyDown('d'))
	{
		camera->moveRight(speed*0.1f);
	}
	float *newEye = camera->getEye();
	playerBody->activate(true);
	playerBody->setLinearVelocity(100*btVector3(newEye[0]-oldEye[0],-0.04,newEye[2]-oldEye[2]));

	// check physics
	dynamicsWorld->stepSimulation(1.f/60.f,10);

	// update camera
	btVector3 camPos = playerBody->getWorldTransform().getOrigin();
	camera->setPosition(camPos[0],camPos[1]+0.8,camPos[2]);
	Profiler::getInstance()->endProfile();
}