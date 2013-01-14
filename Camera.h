#ifndef CAMERA_H
#define CAMERA_H

#include <windows.h>
#include <Gl/gl.h>
#include <GL/glu.h>
#include "Matrix.h"
#include "MatrixManager.h"

class Camera
{
protected:
	float eyePos[3];
	float lookAt[3];
	float up[3];
	float right[3];
	float hAngle;
	float vAngle;
	int lastMouseX, lastMouseY;

	float rotSpeed;

public:
	Camera();

	void mouseRotate();

	virtual void move(float speed);
	virtual void moveForward(float speed);
	virtual void moveBackward(float speed);
	virtual void moveLeft(float speed);
	virtual void moveRight(float speed);
	virtual void moveUp(float speed);
	virtual void moveDown(float speed);

	void recalculate();

	void transform();
	glm::mat4 transformToMatrix(glm::mat4 matrix);

	void setPosition(float x, float y, float z);
	void setLookAt(float x, float y, float z);
	void setUp(float x, float y, float z);
	void setRight(float x, float y, float z);
	void setRotSpeed(float speed);
	float geteyeX();
	float geteyeY();
	float geteyeZ();
	float *getEye();
	Vector3 geteyeV();
	Vector3 getLookAt();
	Vector3 getUp();
	Vector3 getRight();
};

#endif
