#include <QtGui>
#include "QtCamera.h"

void QtCamera::move(float speed) {
	if (Root::inputManager->isKeyDown(Qt::Key_W))
		moveForward(speed*0.1f);
	if (Root::inputManager->isKeyDown(Qt::Key_S))
		moveBackward(speed*0.1f);
	if (Root::inputManager->isKeyDown(Qt::Key_A))
		moveLeft(speed*0.1f);
	if (Root::inputManager->isKeyDown(Qt::Key_D))
		moveRight(speed*0.1f);
	if (Root::inputManager->isKeyDown(Qt::Key_E))
		moveUp(speed*0.1f);
	if (Root::inputManager->isKeyDown(Qt::Key_Q))
		moveDown(speed*0.1f);

	if (Root::inputManager->isMouseButtonDown(Qt::RightButton)) {
		mouseRotate();
	} else {
		lastMouseX = -1;
		lastMouseY = -1;
	}
}