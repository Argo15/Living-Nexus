#ifndef MAINGRAPHICSWIDGET_H
#define MAINGRAPHICSWIDGET_H

#include <QGLWidget>
#include <QtGui>
#include "View.h"
#include "Camera.h"
#include "TileManager.h"

class MainGraphicsWidget : public QGLWidget
{
    Q_OBJECT

private:
    int fps;
	View *view;
	Camera *camera;
	TileManager *tileManager;

protected:
    void initializeGL();
    void resizeGL(int width, int height);
	void paintGL() {update(fps); render();}
	void keyPressEvent (QKeyEvent *event);
	void keyReleaseEvent (QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);	

public:
	MainGraphicsWidget(QGLFormat fmt, QWidget *parent = 0);

    void update(float fps);
	void render();
};

#endif