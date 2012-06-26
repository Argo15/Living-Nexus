#ifndef MESH_H
#define MESH_H

#include <string>

class Mesh {
private:
	string name;

	int numTriangles;
	float center[3];
	float radius;
	float *vertex;
	float *texture;
	float *normal;
	float *tangentbuf;
	float *bitangentbuf;

public:
	void load(const char *filename);
};

#endif