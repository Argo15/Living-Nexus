#include "DockedWidget.h"
#include "FileWidget.h"
#include "ModelWidget.h"
#include "TextureWidget.h"
#include "MaterialWidget.h"

DockedWidget::DockedWidget(QGLWidget *glWidget) 
	: QDockWidget(0)
{
	QWidget *mainWidget = new QWidget();
	QVBoxLayout *mainLayout = new QVBoxLayout;
		QHBoxLayout *modelTextureLayout = new QHBoxLayout;

	modelTextureLayout->addWidget(ModelWidget::getInstance(glWidget));
	modelTextureLayout->addWidget(TextureWidget::getInstance(glWidget));

	mainLayout->addWidget(FileWidget::getInstance());
	mainLayout->addWidget(new QSplitter(Qt::Vertical));
	mainLayout->addLayout(modelTextureLayout);
	mainLayout->addWidget(MaterialWidget::getInstance(glWidget));
	mainLayout->setContentsMargins(0,0,0,0);

	mainWidget->setLayout(mainLayout);
	mainWidget->setFixedHeight(mainWidget->sizeHint().height());
	mainWidget->setFixedWidth(400);

	QScrollArea *scrollArea = new QScrollArea;
	scrollArea->setWidget(mainWidget);

	setWidget(scrollArea);
}
