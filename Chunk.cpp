#include "Chunk.h"
#include "Root.h"
#include "WorldState.h"

Chunk::Chunk() : Transformable()
{
	numActors = 0;
	actors = 0;
	orientation = 0;
	radius = 0;
	for (int i=0; i<10; i++) {
		for (int j=0; j<10; j++) {
			tileModes[i][j] = 0;
		}
	}
}

void Chunk::drawChunk(string shader) 
{
	Root::ModelviewMatrix.push(Root::ModelviewMatrix.top());
	Root::NormalMatrix.push(Root::NormalMatrix.top());
		transformToMatrix(&Root::ModelviewMatrix.top());
		transformToMatrix(&Root::NormalMatrix.top());
		glm::mat4 normMat(Root::NormalMatrix.top());
		normMat[3] = glm::vec4(0,0,0,1.0f);
		Root::ModelviewMatrix.top() = glm::rotate(Root::ModelviewMatrix.top(), 90.0f*orientation, glm::vec3(0,1.0f,0));
		normMat = glm::rotate(normMat, 90.0f*orientation, glm::vec3(0,1.0f,0));
		Root::NormalMatrix.top() = glm::mat3(normMat);
		for (int i=0; i<numActors; i++) {
			Root::ModelviewMatrix.push(Root::ModelviewMatrix.top());
			Root::NormalMatrix.push(Root::NormalMatrix.top());
				actors[i]->transformToMatrix(&Root::ModelviewMatrix.top());
				actors[i]->transformToMatrix(&Root::NormalMatrix.top());
				actors[i]->drawActor(shader);
			Root::ModelviewMatrix.pop();
			Root::NormalMatrix.pop();
		}
	Root::ModelviewMatrix.pop();
	Root::NormalMatrix.pop();
}

bool Chunk::loadChunk(string filename)
{
	ifstream file(filename.c_str(), ios::in|ios::binary|ios::ate);
	if (file.is_open())
	{ 
		file.seekg (0, ios::beg);
		file.read((char*)&numActors,sizeof(numActors));
		SaveActor *loadActors = new SaveActor[numActors];
		actors = new Actor*[numActors];
		file.read((char*)loadActors,sizeof(SaveActor)*numActors);

		for(int i=0; i<numActors; i++) {
			string *model = Root::modelManager->getModel(loadActors[i].model)->getName();
			string *mat = Root::materialManager->getMaterial(loadActors[i].material)->getName();
			actors[i] = new Actor(model, mat);
			actors[i]->setName(loadActors[i].name);
			actors[i]->setTranslate(loadActors[i].translation[0],loadActors[i].translation[1],loadActors[i].translation[2]);
			actors[i]->setRotate(Quaternion(loadActors[i].rotation[0],loadActors[i].rotation[1],loadActors[i].rotation[2],loadActors[i].rotation[3]));
			actors[i]->setScale(loadActors[i].scale[0],loadActors[i].scale[1],loadActors[i].scale[2]);
			float actorRadius = actors[i]->getTranslateV().length()+actors[i]->getScaledRadius();
			if (actorRadius>radius)
				radius=actorRadius;
		}

		file.read((char*)&numPhysics,sizeof(numPhysics));
		SavePhysics *loadPhysics = new SavePhysics[numPhysics];
		physics = new PhysicsShape*[numPhysics];
		file.read((char*)loadPhysics,sizeof(SavePhysics)*numPhysics);

		for(int i=0; i<numPhysics; i++) {
			physics[i] = new PhysicsShape(loadPhysics[i].physicsType);
			physics[i]->setTranslate(loadPhysics[i].translation[0],loadPhysics[i].translation[1],loadPhysics[i].translation[2]);
			physics[i]->setRotate(Quaternion(loadPhysics[i].rotation[0],loadPhysics[i].rotation[1],loadPhysics[i].rotation[2],loadPhysics[i].rotation[3]));
			physics[i]->setScale(loadPhysics[i].scale[0],loadPhysics[i].scale[1],loadPhysics[i].scale[2]);
		}

		file.read((char*)tileModes,sizeof(tileModes));

		file.close();

		int start_pos = filename.rfind("/")+1;
		int end_pos = filename.rfind(".");
		string name = filename.substr(start_pos,end_pos-start_pos);
		setName(name);

		return true;
	}
	return false;
}

float Chunk::getRadius()
{
	return radius;
}

void Chunk::addPhysicsToDynamicWorld(PhysicsManager *physicsManager)
{
	BulletManager *bullet = physicsManager->getBulletManager();
	for (int i=0; i<numPhysics; i++) {
		PhysicsShape physicsShape = *physics[i];
		physicsShape.matrix = glm::mat4(1.0f);
		transformToMatrix(&physicsShape.matrix);
		physicsShape.matrix = glm::rotate(physicsShape.matrix, 90.0f*orientation, glm::vec3(0,1.0f,0));
		glm::mat4 mat = glm::mat4(1.0f);
		mat = glm::translate(mat, glm::vec3(physicsShape.getTranslate()[0],physicsShape.getTranslate()[1],physicsShape.getTranslate()[2]));
		glm::quat rot = glm::quat(physicsShape.getRotate()[0],physicsShape.getRotate()[1],physicsShape.getRotate()[2],physicsShape.getRotate()[3]);
		mat = mat * glm::mat4_cast(rot);
		physicsShape.matrix = physicsShape.matrix * mat;
		bullet->addPhysicsShape(&physicsShape);
	}
}

int Chunk::getTileMode(int x, int y) {
	int worldX = x;
	int worldY = y;
	if (orientation == 3) {
		worldX = y;
		worldY = 9-x;
	}
	if (orientation == 2) {
		worldX = 9-x;
		worldY = 9-y;
	}
	if (orientation == 1) {
		worldX = 9-y;
		worldY = x;
	}
	return tileModes[worldX][worldY];
}