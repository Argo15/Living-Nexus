#include "DockedWidget.h"
#include "FileWidget.h"
#include "ModelWidget.h"
#include "TextureWidget.h"
#include "MaterialWidget.h"
#include "ActorWidget.h"
#include "DisplayWidget.h"

DockedWidget::DockedWidget(QGLWidget *glWidget) 
	: QDockWidget(0)
{
	QWidget *mainWidget = new QWidget();
	QVBoxLayout *mainLayout = new QVBoxLayout;
		QHBoxLayout *modelTextureLayout = new QHBoxLayout;
		QHBoxLayout *actorDisplayLayout = new QHBoxLayout;

	modelTextureLayout->addWidget(ModelWidget::getInstance(glWidget));
	modelTextureLayout->addWidget(TextureWidget::getInstance(glWidget));

	actorDisplayLayout->addWidget(ActorWidget::getInstance());
	actorDisplayLayout->addWidget(DisplayWidget::getInstance());

	mainLayout->addWidget(FileWidget::getInstance());
	mainLayout->addWidget(new QSplitter(Qt::Vertical));
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
