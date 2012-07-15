#ifndef DOCKEDTILECHOOSER_H
#define DOCKEDTILECHOOSER_H

#include <QGLWidget>
#include <QtGui>
#include "TileChooserMainWidget.h"

class DockedTileChooser : public QDockWidget
{
    Q_OBJECT

private: 
	DockedTileChooser(QGLWidget *glWidget);
	static DockedTileChooser* pInstance;

	TileChooserMainWidget *mainWidget;

public:
	static DockedTileChooser* Instance();
    static void Initialize(QGLWidget *glWidget);
};

#endif