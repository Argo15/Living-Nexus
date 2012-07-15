#ifndef DOCKEDPHYSICSWIDGET_H
#define DOCKEDPHYSICSWIDGET_H

#include <QGLWidget>
#include <QtGui>
#include "PhysicsWidget.h"

class DockedPhysicsWidget : public QDockWidget
{
    Q_OBJECT

private: 
	PhysicsWidget *widget;

	DockedPhysicsWidget();
	static DockedPhysicsWidget* pInstance;

public:
	static DockedPhysicsWidget* Instance();
    static void Initialize();
};

#endif