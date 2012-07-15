#include "DockedWidget.h"

DockedWidget::DockedWidget() 
	: QWidget(0)
{
	QVBoxLayout *mainLayout = new QVBoxLayout;

	setLayout(mainLayout);
	layout()->setContentsMargins(0,0,0,0);

	setFixedHeight(sizeHint().height());
	setFixedWidth(sizeHint().width());
}
