#ifndef PHYSICSWIDGET_H
#define PHYSICSWIDGET_H

#include <QWidget>
#include <QtGui>
#undef __glext_h_
#undef __glxext_h_
#undef __gl_h_
#include <GL/GLee.h>
#include "PhysicsShape.h"

class PhysicsWidget : public QWidget
{
    Q_OBJECT

private:

	QPushButton *cubeShapeBtn, *cylinderShapeBtn, *sphereShapeBtn;
	QLabel *addShapeLbl;

public:
	PhysicsWidget();
	~PhysicsWidget(){}

public slots:
	void addBox();
	void addCylinder();
	void addSphere();
};

#endif