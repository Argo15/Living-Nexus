#include "Chunk.h"
#include "TileManager.h"
#include "Unproject.h"

Chunk::Chunk() 
{
	for (int i=0; i<10; i++) {
		for (int j=0; j<10; j++) {
			tiles[i][j] = TileManager::Instance()->getTile("Green Tile");
			tileMode[i][j] = 0;
			canUpdate[i][j] = true;
			rotate[i][j] = 0;
		}
	}
	currentTile = 0;
	currentRotate = 0;
	selectedX = 2;
	selectedZ = 2;
}

void Chunk::drawChunk(GLSLProgram *program)
{
	for (int i=0; i<10; i++) {
		for (int j=0; j<10; j++) {
			glPushMatrix();
				if (currentTile != 0 && selectedX == i && selectedZ == j) {
					glTranslatef(i-5,0,j-5);
					glTranslatef(0.5,0,0.5);
					glRotatef(currentRotate*90,0,1,0);
					glTranslatef(-0.5,0,-0.5);
					currentTile->drawTile(program);
				} else {
					glTranslatef(i-5,0,j-5);
					glTranslatef(0.5,0,0.5);
					glRotatef(rotate[i][j]*90,0,1,0);
					glTranslatef(-0.5,0,-0.5);
					tiles[i][j]->drawTile(program);
				}
			glPopMatrix();
		}
	}
}

void Chunk::update(int mouseX, int mouseY, bool mouseClick) 
{
	if (!mouseClick) {
		for (int i=0; i<10; i++) {
			for (int j=0; j<10; j++) {
				canUpdate[i][j] = true;
			}
		}
	}
	ArgoVector3 mousePos = getUnproject(0.0,mouseX,mouseY);
	ArgoVector3 mouseRay = getUnproject(1.0,mouseX,mouseY) - mousePos;
	mouseRay.normalize();
	float t = (-1.0*mousePos[1])/mouseRay[1];
	ArgoVector3 intersect = mousePos + mouseRay * t;
	selectedX = (int)(intersect[0]+5);
	selectedZ = (int)(intersect[2]+5);
	if (canUpdate[selectedX][selectedZ] && mouseClick && selectedX > -1 && selectedX < 10 && selectedZ > -1 && selectedZ < 10) {
		if (tiles[selectedX][selectedZ] == TileManager::Instance()->getTile("Yellow Tile")) {
			tiles[selectedX][selectedZ] = TileManager::Instance()->getTile("Green Tile");
			tileMode[selectedX][selectedZ] = 0;
		} else if (tiles[selectedX][selectedZ] == TileManager::Instance()->getTile("Green Tile")) {
			tiles[selectedX][selectedZ] = TileManager::Instance()->getTile("Red Tile");
			tileMode[selectedX][selectedZ] = 1;
		} else {
			tiles[selectedX][selectedZ] = TileManager::Instance()->getTile("Yellow Tile");
			tileMode[selectedX][selectedZ] = 2;
		}
		canUpdate[selectedX][selectedZ] = false;
		rotate[selectedX][selectedZ] = currentRotate;
	}
}