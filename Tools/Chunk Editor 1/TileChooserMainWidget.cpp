#include "TileChooserMainWidget.h"

TileChooserMainWidget::TileChooserMainWidget(QGLWidget *glWidget) 
{
	buttonWidget = new QPushButton("Rotate");
	chooserWidget = new TileChooserWidget(this,glWidget);
	buttonWidget->setFixedWidth(60);
	chooserWidget->setFixedWidth(800);

	QHBoxLayout *mainLayout = new QHBoxLayout;

	mainLayout->addWidget(buttonWidget);
	mainLayout->addWidget(chooserWidget);

	setLayout(mainLayout);

	connect(buttonWidget, SIGNAL(clicked()),chooserWidget, SLOT(rotateTiles()));

	layout()->setContentsMargins(0,0,0,0);

	setFixedHeight(125);
	setFixedWidth(sizeHint().width());
}