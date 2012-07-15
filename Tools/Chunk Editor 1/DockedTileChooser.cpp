#include "DockedTileChooser.h"

DockedTileChooser *DockedTileChooser::pInstance = 0;

void DockedTileChooser::Initialize(QGLWidget *glWidget)
{
	if (pInstance != 0) {
		delete pInstance;
	}
	pInstance=new DockedTileChooser(glWidget);
}

DockedTileChooser *DockedTileChooser::Instance()
{
	return pInstance;
}

DockedTileChooser::DockedTileChooser(QGLWidget *glWidget)
	: QDockWidget("Tile Chooser")
{
	mainWidget = new TileChooserMainWidget(glWidget);

	setWidget(mainWidget);
}