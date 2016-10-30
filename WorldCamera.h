#ifndef WORLDCAMERA_H
#define WORLDCAMERA_H

#include "Camera.h"

/*
 * Author: wcrane
 * Date: 3/15/2013
 *
 * Camera object used in the world environment.
 */
class WorldCamera : public Camera
{
private:
	float m_nSpeedFactor;

public:
	WorldCamera();

	// Basic move controlls based on the WASD keys
	void move(float nSpeed);
	void moveForward(float nSpeed);
	void moveBackward(float nSpeed);
	void moveLeft(float nSpeed);
	void moveRight(float nSpeed);
	void moveUp(float nSpeed);
	void moveDown(float nSpeed);
};

#endif