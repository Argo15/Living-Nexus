#include "WorldChunks.h"
#include "WorldState.h"
#include <time.h>

WorldChunks::WorldChunks(int w, int h)
{
	width = w;
	height = h;
	worldChunks = new Chunk**[w];
	for (int i=0; i<w; i++) {
		worldChunks[i] = new Chunk*[h];
		for (int j=0; j<h; j++) {
			worldChunks[i][j] = new Chunk();
		}
	}
}

void WorldChunks::generateChunks(ChunkManager *chunks, PhysicsManager *physicsManager) {
	string chunkNames[12];
	chunkNames[0] = "Flat Chunk";
	chunkNames[1] = "River Chunk";
	chunkNames[2] = "River Corner Chunk";
	chunkNames[3] = "Wall Chunk";
	chunkNames[4] = "Wall Corner Chunk";
	chunkNames[5] = "Bridge River Chunk";
	chunkNames[6] = "Bridge River Corner Chunk";
	chunkNames[7] = "Water Plane";
	chunkNames[8] = "Beach Chunk";
	chunkNames[9] = "Beach River Chunk";
	chunkNames[10] = "Invisible Wall";

	srand ( time(NULL) );

	int leftCount = 0;
	int rightCount = 0;
	do {
		allChunks = new vector<Chunk *>();

		leftCount = 0;
		rightCount = 0;
		int bridgeCount = 0;

		// build a flat world
		for (int i=0; i<width; i++) {
			for (int j=0; j<height-1; j++) {
				*worldChunks[i][j] = *(chunks->getChunk(chunkNames[0]));
				worldChunks[i][j]->setTranslate(i*10.0f,0,j*10.0f);
			}
		}
		for (int i=0; i< width; i++) {
			*worldChunks[i][height-1] = *(chunks->getChunk(chunkNames[8]));
			worldChunks[i][height-1]->setTranslate(i*10.0f,0,(height-1)*10.0f);
		}

		// pick a place to start a river
		glm::ivec2 startpoint;
		do {
			startpoint = glm::ivec2(rand()%(width-4)+2,0);
		} while (abs(startpoint.x-width/2) < 2);
		*worldChunks[startpoint.x][startpoint.y] = *(chunks->getChunk(chunkNames[1]));
		worldChunks[startpoint.x][startpoint.y]->setTranslate(startpoint.x*10.0f,0,startpoint.y*10.0f);
		worldChunks[startpoint.x][startpoint.y]->setOrientation(1);
		Chunk *waterChunk = new Chunk();
		*waterChunk = *(chunks->getChunk(chunkNames[7]));
		waterChunk->setTranslate(startpoint.x*10.0f,0,startpoint.y*10.0f);
		allChunks->push_back(waterChunk);

		// carve out a river
		glm::ivec2 currentPoint = startpoint;
		int direction = 0;
		int lastDirection = 0;
		int lookingDir = 0;
		int orientation = 0;
		do {
			// get current location
			if (direction == 0){
				currentPoint.y = currentPoint.y + 1;
				orientation = 1;
			}
			if (direction == 1) {
				currentPoint.x = currentPoint.x + 1;
				orientation = 0;
			}
			if (direction == 2) {
				currentPoint.x = currentPoint.x - 1;
				orientation = 0;
			}

			// determine if we need to add a bridge
			int bridgeOffset = 0;
			if ((currentPoint.y > 1 && bridgeCount < 1) || (currentPoint.y > 4 && bridgeCount < 2) || (currentPoint.y > 7 && bridgeCount < 3)) {
				bridgeOffset = 4;
				bridgeCount++;
			}

			// set river chunk, and move a direction
			*worldChunks[currentPoint.x][currentPoint.y] = *(chunks->getChunk(chunkNames[1+bridgeOffset]));
			worldChunks[currentPoint.x][currentPoint.y]->setTranslate(currentPoint.x*10.0f,0,currentPoint.y*10.0f);
			worldChunks[currentPoint.x][currentPoint.y]->setOrientation(orientation);
			lastDirection = direction;
			if (direction == 0 && rand()%2 == 0) {
				direction = rand()%2+1;
			} else if ((direction == 1 ||  direction == 2) && rand()%2 == 0) {
				direction = 0;
			}
			if (currentPoint.x >= width-2 && direction == 1)
				direction = 0;
			if (currentPoint.x <= 1 && direction == 2)
				direction = 0;
			if (currentPoint.y <= 1 || currentPoint.y >= height-2)
				direction = 0;
			if (direction == 1 || direction == 2) {
				if (((*worldChunks[currentPoint.x+3-2*direction][currentPoint.y-1]->getName() == chunkNames[1]) ||
					(*worldChunks[currentPoint.x+3-2*direction][currentPoint.y-1]->getName() == chunkNames[2]) ||
					(*worldChunks[currentPoint.x+3-2*direction][currentPoint.y-1]->getName() == chunkNames[5]) ||
					(*worldChunks[currentPoint.x+3-2*direction][currentPoint.y-1]->getName() == chunkNames[6]))) {
					direction = 0;
				}
			}

			// Check if a turn was made, and replace chunk if needed
			if (direction == 0 && lastDirection != 0 ) {
				*worldChunks[currentPoint.x][currentPoint.y] = *(chunks->getChunk(chunkNames[2+bridgeOffset]));
				worldChunks[currentPoint.x][currentPoint.y]->setTranslate(currentPoint.x*10.0f,0,currentPoint.y*10.0f);
				worldChunks[currentPoint.x][currentPoint.y]->setOrientation(lastDirection + 2);
			} else if ( direction != 0 && lastDirection == 0 ) {
				*worldChunks[currentPoint.x][currentPoint.y] = *(chunks->getChunk(chunkNames[2+bridgeOffset]));
				worldChunks[currentPoint.x][currentPoint.y]->setTranslate(currentPoint.x*10.0f,0,currentPoint.y*10.0f);
				worldChunks[currentPoint.x][currentPoint.y]->setOrientation(direction);
			}

			Chunk *waterChunk = new Chunk();
			*waterChunk = *(chunks->getChunk(chunkNames[7]));
			waterChunk->setTranslate(currentPoint.x*10.0f,0,currentPoint.y*10.0f);
			allChunks->push_back(waterChunk);

		} while (currentPoint.y < height-2 && currentPoint.x < width-1 && currentPoint.x > 0);
		*worldChunks[currentPoint.x][currentPoint.y+1] = *(chunks->getChunk(chunkNames[9]));
		worldChunks[currentPoint.x][currentPoint.y+1]->setTranslate(currentPoint.x*10.0f,0,(currentPoint.y+1)*10.0f);
		worldChunks[currentPoint.x][currentPoint.y+1]->setOrientation(direction);
		for (int j=0; j<height; j++) {
			bool left = true;
			for (int i=0; i<width; i++) {
				if (*worldChunks[i][j]->getName() == chunkNames[0]) {
					if (left)
						leftCount++;
					else
						rightCount++;
				}
				if (((*worldChunks[i][j]->getName() == chunkNames[1]) ||
					(*worldChunks[i][j]->getName() == chunkNames[2]) ||
					(*worldChunks[i][j]->getName() == chunkNames[5]) ||
					(*worldChunks[i][j]->getName() == chunkNames[6]))) {
					left = false;
				}
			}
		}
	} while (abs(leftCount-rightCount) > 5);

	// add the edges
	for (int i=0; i< width; i++) {
		Chunk *edgeChunk = new Chunk();
		*edgeChunk = *(chunks->getChunk(chunkNames[3]));
		edgeChunk->setTranslate(i*10.0f,0,-10.0f);
		edgeChunk->setOrientation(2);
		allChunks->push_back(edgeChunk);
	}
	for (int i=0; i<height; i++) {
		Chunk *edgeChunk = new Chunk();
		*edgeChunk = *(chunks->getChunk(chunkNames[3]));
		edgeChunk->setTranslate(-10.0f,0,i*10.0f);
		edgeChunk->setOrientation(3);
		allChunks->push_back(edgeChunk);
		edgeChunk = new Chunk();
		*edgeChunk = *(chunks->getChunk(chunkNames[3]));
		edgeChunk->setTranslate(width*10.0f,0,i*10.0f);
		edgeChunk->setOrientation(1);
		allChunks->push_back(edgeChunk);
	}

	// add ocean
	for (int i=-3; i<width+3; i++) {
		for (int j=0; j<3; j++) {
			Chunk *waterChunk = new Chunk();
			*waterChunk = *(chunks->getChunk(chunkNames[7]));
			waterChunk->setTranslate(i*10.0f,0,(height+j)*10.0f);
			allChunks->push_back(waterChunk);
		}
	}

	// add the corners
	Chunk *cornerChunk = new Chunk();
	*cornerChunk = *(chunks->getChunk(chunkNames[4]));
	cornerChunk->setTranslate(-10.0f,0,-10.0f);
	allChunks->push_back(cornerChunk);
	cornerChunk = new Chunk();
	*cornerChunk = *(chunks->getChunk(chunkNames[4]));
	cornerChunk->setTranslate(width*10.0f,0,-10.0f);
	allChunks->push_back(cornerChunk);
	cornerChunk = new Chunk();
	/*cornerChunk = *(chunks->getChunk(chunkNames[4]));
	cornerChunk->setTranslate(width*10.0f,0,height*10.0f);
	allChunks->push_back(cornerChunk);
	cornerChunk = new Chunk();
	*cornerChunk = *(chunks->getChunk(chunkNames[4]));
	cornerChunk->setTranslate(-10.0f,0,height*10.0f);
	allChunks->push_back(cornerChunk);*/

	// add world chunks to array
	for (int i=0; i<width; i++) {
		for (int j=0; j<height; j++) {
			allChunks->push_back(worldChunks[i][j]);
		}
	}

	// add physics to world
	for (vector<Chunk *>::iterator i = allChunks->begin(); i != allChunks->end(); i++) {
		(*i)->addPhysicsToDynamicWorld(physicsManager);
	}
}

vector<Chunk *> *WorldChunks::getAllChunks() {
	return allChunks;
}

vector<Chunk *> *WorldChunks::getVisibleChunks(Frustum *frustum) {
	vector<Chunk *> *chunks = new vector<Chunk *>();
	for (vector<Chunk *>::iterator i = allChunks->begin(); i != allChunks->end(); i++) {
		if (frustum->isInFrustum((*i)->getTranslateV(),(*i)->getRadius())) {
			chunks->push_back((*i));
		}
	}
	return chunks;
}