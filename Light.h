#ifndef LIGHT_H
#define LIGHT_H

#include <string>
using namespace std;

class Light
{
protected:
	float color[3];
	float ambient;
	float diffuse;
	float specular;
	bool enabled;

public:
	void setAmbient(float amt);
	void setDiffuse(float amt);
	void setSpecular(float amt);
	float getDiffuse();
	float getAmbient();
	float getSpecular();
	void setColor(float r, float g, float b);
	float *getColor();
	bool isenabled();
	void setEnabled(bool enabled);
	virtual void sendToShader(string shader) = 0;
};

#endif