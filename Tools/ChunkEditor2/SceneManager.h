#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <vector>
#include "Actor.h"
#include "Tile.h"
#include "TileManager.h"
#include "ChunkManager.h"
#include "Logger.h"
#include "Transformer.h"
#include "SceneTiles.h"

class Transformer;

class SceneManager {
private:
	static SceneManager *m_pInstance;
	std::map<int, Actor *> *actors;		// ActorId -> Actor
	int nextActorId;
	TileManager *tileManager;
	ChunkManager *chunkManager;
	int selectedActorId;
	SceneManager();

	SceneTiles *sceneTiles;
	int editMode;

	bool displayScene, displayPhysics, displayTiles;

	QGLWidget *glWidget;

public:
	static SceneManager *getInstance();
	int addActor(Actor *actor);			// returns an actorId
	void removeActor(int actorId);
	void removeSelected();
	void addChunk(Chunk *chunk);
	void addChunk(string chunk);
	void addTile(string tile);
	void clear();
	void draw();
	void drawTransformers();
	void setSelectedActor(int id);
	Actor *getSelectedActor();
	std::map<int, Actor *> *getActors() {return actors;}

	TileManager *getTileManager() {return tileManager;}
	ChunkManager *getChunkManager() {return chunkManager;}

	void setGLWidget(QGLWidget *widget) {glWidget = widget;}
	QGLWidget *getGLWidget() {return glWidget;}

	void setDisplayScene(bool value) {displayScene = value;}
	void setDisplayPhysics(bool value) {displayPhysics = value;}
	void setDisplayTiles(bool value) {displayTiles = value;}
	bool getDisplayScene() {return displayScene;}
	bool getDisplayPhysics() {return displayPhysics;}
	bool getDisplayTiles() {return displayTiles;}

	void setEditMode(int value) {editMode = value;}
	int getEditMode() {return editMode;}

	SceneTiles *getSceneTiles() {return sceneTiles;}
};

#endif