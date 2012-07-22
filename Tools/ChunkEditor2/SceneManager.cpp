#include "SceneManager.h"

SceneManager* SceneManager::m_pInstance = 0;

SceneManager::SceneManager() {
	nextActorId = 1;
}

SceneManager *SceneManager::getInstance() {
	if (m_pInstance == 0) {
		m_pInstance = new SceneManager();
	}
	return m_pInstance;
}