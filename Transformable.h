#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H

#include "Matrix.h"

class Transformable {
protected:
	float translations[3];
	Quaternion rotation;
	float scale[3];

public:
	Transformable();

	void transform();
	glm::mat4 transformToMatrix(glm::mat4 matrix);
	glm::mat3 transformToMatrix(glm::mat3 matrix);

	void Translate(float x, float y, float z);
	void Rotate(Quaternion quat);
	void Scale(float x, float y, float z);
	void setTranslate(float x, float y, float z);
	void setRotate(Quaternion quat);
	void setScale(float x, float y, float z);
	float *getTranslate();
	Quaternion getRotate();
	float *getScale();
	Vector3 getTranslateV();
};

#endif