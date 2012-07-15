#ifndef TILECHOOSERWIDGET_H
#define TILECHOOSERWIDGET_H

#include <QtOpenGL>
#include <QGLWidget>
#include <QtGui>
#undef __glext_h_
#undef __glxext_h_
#undef __gl_h_
#include <GL/GLee.h>
#include "ArgoView.h"
using namespace std;

class TileChooserWidget : public QGLWidget
{
    Q_OBJECT

private:
	ArgoView *view;
	int currentTile;
	int rotate;

protected:
    void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();
	void wheelEvent(QWheelEvent *event);

public:
	TileChooserWidget(QWidget *parent = 0, const QGLWidget * shareWidget = 0);

public slots:
	void rotateTiles();
};

#endif