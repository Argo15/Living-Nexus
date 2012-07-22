#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <vector>
#include "Actor.h"

class SceneManager {
private:
	static SceneManager *m_pInstance;
	std::map<int, Actor *> *actors;		// ActorId -> Actor
	int nextActorId;

	SceneManager();

public:
	static SceneManager *getInstance();
};

#endif