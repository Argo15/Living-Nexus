#include "Tile.h"
#include "ArgoMaterialManager.h"
#include "ArgoModelManager.h"

void Tile::drawTileSelection() {
	for (int i=0; i<actors.size(); i++) {
		glPushMatrix();
			actors[i]->transform();
			ArgoMaterialManager::Instance()->UseMaterial(*actors[i]->getMaterial());
			ArgoModelManager::Instance()->DrawModelSelection(*actors[i]->getModel());
		glPopMatrix();
	}
}

void Tile::drawTile(GLSLProgram *program) {
	for (int i=0; i<actors.size(); i++) {
		glPushMatrix();
			actors[i]->transform();
			ArgoMaterialManager::Instance()->UseMaterial(*actors[i]->getMaterial(),program);
			if (program == 0)
				ArgoModelManager::Instance()->DrawModelSelection(*actors[i]->getModel());
			else
				ArgoModelManager::Instance()->DrawModel(*actors[i]->getModel());
		glPopMatrix();
	}
}