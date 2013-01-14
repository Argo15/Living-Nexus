#include <GL/freeglut.h>
#include <math.h>
#include "Camera.h"
#include "GameState.h"
#include "InputManager.h"

#define PI 3.141592653589793

Camera::Camera()
{
	hAngle=-(float)PI/4.0f;
    vAngle=(float)PI/4.0f;
	eyePos[0]=5.0; eyePos[1]=5.0; eyePos[2]=5.0; 
	recalculate();
	rotSpeed=0.8;
	lastMouseX = -1;
	lastMouseY = -1;
}

void Camera::mouseRotate()
{
	int mouseX=InputManager::getInstance()->getMouseX();
	int mouseY=InputManager::getInstance()->getMouseY();

	if (lastMouseX == -1)
	{
		lastMouseX = mouseX;
		lastMouseY = mouseY;
		return;
	}

	int dx = mouseX - lastMouseX;
	int dy = mouseY - lastMouseY;

	hAngle-=(float)dx*rotSpeed*0.005f;
	vAngle+=(float)dy*rotSpeed*0.005f;

	if (vAngle>0.999f*PI/2.0f)
	{
        vAngle=0.999f*(float)PI/2.0f;
	}
    if (vAngle<-0.999f*PI/2.0f)
	{
        vAngle=-0.999f*(float)PI/2.0f;
	}

	recalculate();

	lastMouseX = mouseX;
	lastMouseY = mouseY;
	
	if (GameState::GAMESTATE->mouseHidden()) 
	{
		if (mouseX>500) 
		{
			glutWarpPointer(300, mouseY);
			lastMouseX = 300;
		}
		if (mouseX<300) 
		{
			glutWarpPointer(500, mouseY);
			lastMouseX = 500;
		}
		if (mouseY>500) 
		{
			glutWarpPointer(mouseX, 300);
			lastMouseY = 300;
		}
		if (mouseY<300) 
		{
			glutWarpPointer(mouseX, 500);
			lastMouseY = 500;
		}
	}
}

void Camera::move(float speed)
{
	if (InputManager::getInstance()->isKeyDown('w'))
	{
		moveForward(speed*0.1f);
	}
	if (InputManager::getInstance()->isKeyDown('s'))
	{
		moveBackward(speed*0.1f);
	}
	if (InputManager::getInstance()->isKeyDown('a'))
	{
		moveLeft(speed*0.1f);
	}
	if (InputManager::getInstance()->isKeyDown('d'))
	{
		moveRight(speed*0.1f);
	}
	if (InputManager::getInstance()->isKeyDown('e'))
	{
		moveUp(speed*0.1f);
	}
	if (InputManager::getInstance()->isKeyDown('q'))
	{
		moveDown(speed*0.1f);
	}

	mouseRotate();
}

void Camera::moveForward(float speed)
{
	eyePos[0]-=cos(hAngle)*speed;
	eyePos[2]+=sin(hAngle)*speed;
	lookAt[0]-=cos(hAngle)*speed;
	lookAt[2]+=sin(hAngle)*speed;
}

void Camera::moveBackward(float speed)
{
	eyePos[0]+=cos(hAngle)*speed;
	eyePos[2]-=sin(hAngle)*speed;
	lookAt[0]+=cos(hAngle)*speed;
	lookAt[2]-=sin(hAngle)*speed;
}

void Camera::moveLeft(float speed)
{
	eyePos[2]+=cos(hAngle)*speed;
	eyePos[0]+=sin(hAngle)*speed;
	lookAt[2]+=cos(hAngle)*speed;
	lookAt[0]+=sin(hAngle)*speed;
}

void Camera::moveRight(float speed)
{
	eyePos[2]-=cos(hAngle)*speed;
	eyePos[0]-=sin(hAngle)*speed;
	lookAt[2]-=cos(hAngle)*speed;
	lookAt[0]-=sin(hAngle)*speed;
}

void Camera::moveUp(float speed)
{
	eyePos[1]+=speed;
	lookAt[1]+=speed;
}

void Camera::moveDown(float speed)
{
	eyePos[1]-=speed;
	lookAt[1]-=speed;
}

void Camera::recalculate()
{
	lookAt[0]=eyePos[0]-cos(hAngle)*abs(cos(vAngle));
	lookAt[1]=eyePos[1]-sin(vAngle);
	lookAt[2]=eyePos[2]+sin(hAngle)*abs(cos(vAngle));
	up[0]=cos(hAngle)*cos(vAngle+(float)PI/2);
	up[1]=sin(vAngle+(float)PI/2);
	up[2]=-sin(hAngle)*cos(vAngle+(float)PI/2);
	Vector3 vLook(lookAt[0]-eyePos[0],lookAt[1]-eyePos[1],lookAt[2]-eyePos[2]);
	Vector3 vUp(up[0],up[1],up[2]);
	Vector3 vRight = vLook.cross(vUp);
	vRight.normalize();
	right[0]=vRight[0];
	right[1]=vRight[1];
	right[2]=vRight[2];
}

void Camera::transform()
{
	MatrixManager::getInstance()->putMatrix4(MODELVIEW, glm::lookAt(
		glm::vec3(eyePos[0],eyePos[1],eyePos[2]),
		glm::vec3(lookAt[0],lookAt[1],lookAt[2]),
		glm::vec3(up[0],up[1],up[2])
	));
}

glm::mat4 Camera::transformToMatrix(glm::mat4 matrix)
{
	return matrix * glm::lookAt(
		glm::vec3(eyePos[0],eyePos[1],eyePos[2]),
		glm::vec3(lookAt[0],lookAt[1],lookAt[2]),
		glm::vec3(up[0],up[1],up[2])
	);
}


void Camera::setPosition(float x, float y, float z)
{
	eyePos[0]=x;
	eyePos[1]=y;
	eyePos[2]=z;
}

void Camera::setLookAt(float x, float y, float z) 
{
	lookAt[0]=x;
	lookAt[1]=y;
	lookAt[2]=z;
}

void Camera::setUp(float x, float y, float z) 
{
	up[0]=x;
	up[1]=y;
	up[2]=z;
}

void Camera::setRight(float x, float y, float z) 
{
	right[0]=x;
	right[1]=y;
	right[2]=z;
}

void Camera::setRotSpeed(float speed) 
{
	rotSpeed=speed;
}

float Camera::geteyeX() 
{
	return eyePos[0];
}

float Camera::geteyeY() 
{
	return eyePos[1];
}

float Camera::geteyeZ() 
{
	return eyePos[2];
}

float *Camera::getEye() 
{
	float *peye = eyePos; 
	return peye;
}

Vector3 Camera::geteyeV() 
{
	return Vector3(eyePos[0],eyePos[1],eyePos[2]);
}

Vector3 Camera::getLookAt() 
{
	return Vector3(lookAt[0],lookAt[1],lookAt[2]);
}

Vector3 Camera::getUp() 
{
	return Vector3(up[0],up[1],up[2]);
}

Vector3 Camera::getRight() 
{
	return Vector3(right[0],right[1],right[2]);
}