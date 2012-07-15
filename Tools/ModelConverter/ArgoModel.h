#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include "ArgoMatrix.h"
using namespace std;

struct Vertex;

struct Triangle {
	Vertex *verts[3];
	ArgoVector3 tan;
	ArgoVector3 bitan;
};

struct Vertex {
	vector<Triangle *> triangles;
	ArgoVector3 pos;
	ArgoVector3 uv;
};

class ArgoModel {
private:
	int numComponents;
	vector<int> componentSizes;

	int numTriangles;
	float radius;
	float center[3];
	float *vertex;
	float *texture;
	float *normal;
	float *tangent;
	float *bitangent;

	void calcTriTangent(Triangle *tri);

public:
	ArgoModel() {}
	~ArgoModel() {}

	void loadModel(const char *filename);
	void calcFlatTangents();
	void calcSmoothTangents();
	void save(string filename);
};