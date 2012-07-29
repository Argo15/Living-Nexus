#include <QtGui>
#include "chunkeditor2.h"
#include "MainGraphicsWidget.h"
#include "DockedWidget.h"
#include "NoState.h"

ChunkEditor2::ChunkEditor2(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	QGLFormat fmt;
	fmt.setDirectRendering(true);
	fmt.setDoubleBuffer(true);
	glWidget = new MainGraphicsWidget(fmt,this);
	setCentralWidget(glWidget);
	startTimer(0);

	dockedWidget = new DockedWidget();

	addDockWidget(Qt::RightDockWidgetArea, dockedWidget);
}

ChunkEditor2::~ChunkEditor2()
{

}

void ChunkEditor2::timerEvent(QTimerEvent *event)
{
	glWidget->repaint();
}

void ChunkEditor2::closeEvent(QCloseEvent *event)
{
	exit(0);
}