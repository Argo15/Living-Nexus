#include "DockedWidget.h"
#include "FileWidget.h"

DockedWidget::DockedWidget() 
	: QDockWidget(0)
{
	QWidget *mainWidget = new QWidget();
	QVBoxLayout *mainLayout = new QVBoxLayout;

	mainLayout->addWidget(FileWidget::getInstance());
	mainLayout->setContentsMargins(0,0,0,0);

	mainWidget->setLayout(mainLayout);
	mainWidget->setFixedHeight(mainWidget->sizeHint().height());
	mainWidget->setFixedWidth(300);

	setWidget(mainWidget);
}
