#ifndef TILECHOOSERMAINWIDGET_H
#define TILECHOOSERMAINWIDGET_H

#include <QGLWidget>
#include <QtGui>
#include "TileChooserWidget.h"

class TileChooserMainWidget : public QWidget {
private:
	QPushButton *buttonWidget;
	TileChooserWidget *chooserWidget;

public:
	TileChooserMainWidget(QGLWidget *glWidget);
	~TileChooserMainWidget(){}
};

#endif