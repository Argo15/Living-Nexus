#include "DockedWidget.h"
#include "FileWidget.h"
#include "ModelWidget.h"
#include "TextureWidget.h"
#include "MaterialWidget.h"
#include "ActorWidget.h"
#include "DisplayWidget.h"
#include "PhysicsWidget.h"

DockedWidget::DockedWidget(QGLWidget *glWidget) 
	: QDockWidget(0)
{
	QWidget *mainWidget = new QWidget();
	QVBoxLayout *mainLayout = new QVBoxLayout;
		QHBoxLayout *filePhysicsLayout = new QHBoxLayout;
		QHBoxLayout *modelTextureLayout = new QHBoxLayout;
		QHBoxLayout *actorDisplayLayout = new QHBoxLayout;

	filePhysicsLayout->addWidget(FileWidget::getInstance());
	filePhysicsLayout->addWidget(PhysicsWidget::getInstance());

	modelTextureLayout->addWidget(ModelWidget::getInstance(glWidget));
	modelTextureLayout->addWidget(TextureWidget::getInstance(glWidget));

	actorDisplayLayout->addWidget(ActorWidget::getInstance());
	actorDisplayLayout->addWidget(DisplayWidget::getInstance());

	mainLayout->addLayout(filePhysicsLayout);
	mainLayout->addLayout(modelTextureLayout);
	mainLayout->addWidget(MaterialWidget::getInstance(glWidget));
	mainLayout->addLayout(actorDisplayLayout);
	mainLayout->setContentsMargins(0,0,0,0);

	mainWidget->setLayout(mainLayout);
	mainWidget->setFixedHeight(mainWidget->sizeHint().height());
	mainWidget->setFixedWidth(400);

	QScrollArea *scrollArea = new QScrollArea;
	scrollArea->setWidget(mainWidget);

	setWidget(scrollArea);
}
