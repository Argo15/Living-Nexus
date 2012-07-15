#include "ArgoModel.h"

void ArgoModel::loadModel(const char *filename)
{
	string line;
	ifstream file(filename);
	char *type = new char[10];
	vector<float> verticies;
	vector<float> texcoords;
	vector<float> normals;
	vector<int> faces;
	float max[3];
	float min[3];
	for (int i=0;i<3;i++){
		max[i]=-1000000000;
		min[i]= 1000000000;
	}
	radius=0.0;
	numComponents=0;
	componentSizes.push_back(0);
	bool firstComponent = true;

	if (file.is_open())
	{
		while ( file.good() )
		{
			getline(file,line);
			float v[3];
			float f[9];
			if (line.size() > 0) {
				sscanf(line.c_str(), "%s %f %f %f\n", type, &v[0], &v[1], &v[2]);
				if (strcmp(type,"v")==0) {
					for (int i=0; i<3; i++) {
						verticies.push_back(v[i]);
						if(v[i]>max[i])
							max[i]=v[i];
						if(v[i]<min[i])
							min[i]=v[i];
					}
				} else if (strcmp(type,"vt")==0) {
					for (int i=0; i<2; i++) {
						texcoords.push_back(v[i]);
					}
				} else if (strcmp(type,"vn")==0) {
					for (int i=0; i<3; i++) {
						normals.push_back(v[i]);
					}
				} else if (strcmp(type,"usemtl")==0) {
					if (firstComponent)
						firstComponent = false;
					else {
						numComponents++;
						componentSizes.push_back(0);
					}
				} else if (strcmp(type,"f")==0) {
					sscanf(line.c_str(), "%s %f/%f/%f %f/%f/%f %f/%f/%f\n", type, &f[0], &f[1], &f[2], &f[3], &f[4], &f[5], &f[6], &f[7], &f[8]);
					for (int i=0; i<9; i++)
						faces.push_back(f[i]);
					componentSizes[numComponents]++;
				}
			}
		}
		file.close();

		for (int i=0;i<3;i++)
			center[i]=(min[i]+max[i])/2.0;

		numTriangles=faces.size()/9;

		vertex = new float[numTriangles*9];
		texture = new float[numTriangles*6];
		normal = new float[numTriangles*9];
		tangent = new float[numTriangles*9];
		bitangent = new float[numTriangles*9];
		float dist;

		for (int i=0; i<numTriangles*3 ; i++){
				vertex[i*3]=verticies[(faces[i*3]-1)*3]-center[0];
				vertex[i*3+1]=verticies[(faces[i*3]-1)*3+1]-center[1];
				vertex[i*3+2]=verticies[(faces[i*3]-1)*3+2]-center[2];
				texture[i*2]=texcoords[(faces[i*3+1]-1)*2];
				texture[i*2+1]=texcoords[(faces[i*3+1]-1)*2+1];
				normal[i*3]=normals[(faces[i*3+2]-1)*3];
				normal[i*3+1]=normals[(faces[i*3+2]-1)*3+1];
				normal[i*3+2]=normals[(faces[i*3+2]-1)*3+2];

				dist=sqrt(pow(vertex[i*3],2)+pow(vertex[i*3+1],2)+pow(vertex[i*3+2],2));

				if(dist>radius)
					radius=dist;
		}
		verticies.clear();
		texcoords.clear();
		normals.clear();
		faces.clear();
	}
}

void ArgoModel::save(string filename)
{
	int offset = 0;
	for (int i=0; i<=numComponents; i++) {
		string saveloc = filename;
		if (i>0) {
			int pos = filename.find(".aobj");
			char buffer[5];
			itoa(i,buffer,5);
			saveloc.insert(pos,buffer);
		}
		ofstream file(saveloc.c_str(), ios::out|ios::binary|ios::ate);
		if (file.is_open())
		{
			float version = 1.0;
			file.write((char*)&version,sizeof(version)); cout << "version: 1.1" << endl;
			file.write((char*)&componentSizes[i],sizeof(int)); cout << "triangles: " << componentSizes[i] << endl;
			file.write((char*)&vertex[offset*9],sizeof(float)*9*componentSizes[i]);
			file.write((char*)&texture[offset*6],sizeof(float)*6*componentSizes[i]);
			file.write((char*)&normal[offset*9],sizeof(float)*9*componentSizes[i]);
			file.write((char*)&tangent[offset*9],sizeof(float)*9*componentSizes[i]);
			file.write((char*)&bitangent[offset*9],sizeof(float)*9*componentSizes[i]);
			file.write((char*)&radius,sizeof(radius));
			file.write((char*)&center,sizeof(center));

			file.close();
		}
		offset+=componentSizes[i];
	}
}

void ArgoModel::calcTriTangent(Triangle *tri)
{
	ArgoVector3 Q1 = tri->verts[1]->pos - tri->verts[0]->pos;
	ArgoVector3 Q2 = tri->verts[2]->pos - tri->verts[0]->pos;
	ArgoVector3 st1 = ArgoVector3(tri->verts[1]->uv[0]-tri->verts[0]->uv[0],
								  tri->verts[1]->uv[1]-tri->verts[0]->uv[1],0);
	ArgoVector3 st2 = ArgoVector3(tri->verts[2]->uv[0]-tri->verts[0]->uv[0],
								  tri->verts[2]->uv[1]-tri->verts[0]->uv[1],0);
	float det = 1.0 / (st1[0]*st2[1] - st2[0]*st1[1]);
	tri->tan = ArgoVector3(Q1[0]*st2[1]-Q2[0]*st1[1],
						   Q1[1]*st2[1]-Q2[1]*st1[1],
					       Q1[2]*st2[1]-Q2[2]*st1[1])*det;
	tri->bitan = ArgoVector3(Q2[0]*st1[0]-Q1[0]*st2[0],
							 Q2[1]*st1[0]-Q1[1]*st2[0],
							 Q2[2]*st1[0]-Q1[2]*st2[0])*det;
	tri->tan.normalize();
	tri->bitan.normalize();
}

void ArgoModel::calcFlatTangents() 
{
	vector<Triangle *> tris;
	for (int i=0; i<numTriangles*3; i+=3){
		Vertex *current[3];
		for (int n=0; n<3; n++) {
			current[n] = new Vertex;
			current[n]->pos.set(vertex[(i+n)*3],vertex[(i+n)*3+1],vertex[(i+n)*3+2]);
			current[n]->uv.set(texture[(i+n)*2],texture[(i+n)*2+1],0.0);
		}
		Triangle *newTri = new Triangle;
		newTri->verts[0]=current[0];
		newTri->verts[1]=current[1];
		newTri->verts[2]=current[2];
		calcTriTangent(newTri);
		tris.push_back(newTri);
	}

	for (int i=0; i<numTriangles; i++) {
		tangent[i*9]=tris[i]->tan[0];
		tangent[i*9+1]=tris[i]->tan[1];
		tangent[i*9+2]=tris[i]->tan[2];
		tangent[i*9+3]=tris[i]->tan[0];
		tangent[i*9+4]=tris[i]->tan[1];
		tangent[i*9+5]=tris[i]->tan[2];
		tangent[i*9+6]=tris[i]->tan[0];
		tangent[i*9+7]=tris[i]->tan[1];
		tangent[i*9+8]=tris[i]->tan[2];
		bitangent[i*9]=tris[i]->bitan[0];
		bitangent[i*9+1]=tris[i]->bitan[1];
		bitangent[i*9+2]=tris[i]->bitan[2];
		bitangent[i*9+3]=tris[i]->bitan[0];
		bitangent[i*9+4]=tris[i]->bitan[1];
		bitangent[i*9+5]=tris[i]->bitan[2];
		bitangent[i*9+6]=tris[i]->bitan[0];
		bitangent[i*9+7]=tris[i]->bitan[1];
		bitangent[i*9+8]=tris[i]->bitan[2];
	}
}

void ArgoModel::calcSmoothTangents()
{
	vector<Vertex *> verts;
	vector<Triangle *> tris;
	for (int i=0; i<numTriangles*3; i+=3){
		Vertex *current[3];
		for (int n=0; n<3; n++) {
			current[n] = new Vertex;
			current[n]->pos.set(vertex[(i+n)*3],vertex[(i+n)*3+1],vertex[(i+n)*3+2]);
			current[n]->uv.set(texture[(i+n)*2],texture[(i+n)*2+1],0.0);
			bool exists = false;
			for (int x=0; x<verts.size(); x++) {
				if (verts[x]->pos == current[n]->pos) {
					current[n] = verts[x];
					exists=true;
				}
			}
			if (!exists) {
				verts.push_back(current[n]);
			}
		}
		Triangle *newTri = new Triangle;
		for (int z=0; z<3; z++) {
			newTri->verts[z]=current[z];
			current[z]->triangles.push_back(newTri);
		}
		tris.push_back(newTri);
	}
}