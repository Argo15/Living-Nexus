#include "SceneManager.h"
#include "DrawFunc.h"

SceneManager* SceneManager::m_pInstance = 0;

SceneManager::SceneManager() {
	nextActorId = 1;
	actors = new std::map<int, Actor *>();
	tileManager = new TileManager();
	chunkManager = new ChunkManager();
	tileManager->Initialize();
	chunkManager->Initialize();
	selectedActorId = -1;
}

SceneManager *SceneManager::getInstance() {
	if (m_pInstance == 0) {
		m_pInstance = new SceneManager();
	}
	return m_pInstance;
}

int SceneManager::addActor(Actor *actor) {
	actors[0][nextActorId] = actor;
	selectedActorId = nextActorId;
	return nextActorId++;
}

void SceneManager::removeActor(int actorId) {
	actors->erase(actorId);
}

void SceneManager::addChunk(Chunk *chunk) {
	Actor **chunkActors = chunk->getActors();
	int numActors = chunk->getNumActors();
	for (int i=0; i<numActors; i++) {
		Actor *newActor = new Actor();
		*newActor = *chunkActors[i];
		addActor(newActor);
	}
}

void SceneManager::addChunk(string chunk) {
	addChunk(chunkManager->getChunk(chunk));
}

void SceneManager::addTile(string tile) {
	addChunk(tileManager->getTile(tile));
}

void SceneManager::clear() {
	actors->clear();
	selectedActorId = -1;
}

void SceneManager::draw() {
	for (map<int,Actor*>::iterator it = actors->begin() ; it != actors->end(); it++ ) {
		Actor *actor = (*it).second;
		Root::ModelviewMatrix.push(Root::ModelviewMatrix.top());
		Root::NormalMatrix.push(Root::NormalMatrix.top());
			actor->transformToMatrix(&Root::ModelviewMatrix.top());
			actor->transformToMatrix(&Root::NormalMatrix.top());
			actor->drawActor("Basic");
		Root::ModelviewMatrix.pop();
		Root::NormalMatrix.pop();
	}
}

Actor *SceneManager::getSelectedActor() {
	if (selectedActorId >= 0) {
		Actor *actor = actors[0][selectedActorId];
		return actor;
	}
	return 0;
}

void SceneManager::drawTransformers() {
	if (selectedActorId >= 0) {
		Actor *actor = actors[0][selectedActorId];
		glPushMatrix();
		transformNoShaders();
		glTranslatef(actor->getTranslate()[0], actor->getTranslate()[1], actor->getTranslate()[2]);
		glDepthFunc(GL_ALWAYS);
		Transformer::draw(false);
		glDepthFunc(GL_LEQUAL);
		glPopMatrix();
	}
}