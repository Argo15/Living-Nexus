#include "DockedPhysicsWidget.h"

DockedPhysicsWidget *DockedPhysicsWidget::pInstance = 0;

void DockedPhysicsWidget::Initialize()
{
	if (pInstance != 0) {
		delete pInstance;
	}
	pInstance=new DockedPhysicsWidget();
}

DockedPhysicsWidget *DockedPhysicsWidget::Instance()
{
	return pInstance;
}

DockedPhysicsWidget::DockedPhysicsWidget()
	: QDockWidget("Physics")
{
	widget = new PhysicsWidget();
	setWidget(widget);
}