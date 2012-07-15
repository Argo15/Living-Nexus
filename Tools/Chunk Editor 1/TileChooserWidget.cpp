#include "TileChooserWidget.h"
#include "TileManager.h"
#include "ArgoSceneManager.h"
#include <vector>
using namespace std;

TileChooserWidget::TileChooserWidget(QWidget *parent, const QGLWidget * shareWidget)
 : QGLWidget(parent,shareWidget)
{
	view = new ArgoView();
	this->setMouseTracking(true);
	currentTile = 0;
	rotate = 0;
}

void TileChooserWidget::initializeGL()
{
	glShadeModel(GL_SMOOTH);				// GL_SMOOTH or GL_FLAT
	glClearDepth(1.0f);						// depth cleared to
	glEnable(GL_DEPTH_TEST);				// enable depth testing
	glEnable(GL_TEXTURE_2D);				// enable texturing
	glDepthFunc(GL_LEQUAL);					// lesser than or equal to depth
	glCullFace(GL_BACK);
}

void TileChooserWidget::resizeGL(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glViewport(0,0,width,height);
	GLfloat aspect = GLfloat(width) / height;
	view->set3D(45.0f,aspect,0.1,100);
	view->set2D(0,1,0,1,0,1);
	glMatrixMode(GL_MODELVIEW);
}

void TileChooserWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	float direction[] = {1.0,1.0,-1.0,0.0};
	float ambient[] = {0.0,0.0,0.0,0.0};
	float diffuse[] = {0.7,0.7,0.7,0.0};
	glLightfv(GL_LIGHT0,GL_POSITION,direction);
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glLineWidth(1.0f);
	glDisable(GL_TEXTURE_2D);

	glLoadIdentity();
	view->use3D(false);
	glTranslatef(0,0,-0.5);
	glBegin(GL_LINES);
		glColor3f(1,1,0);
		glVertex2f(0.45,0.15);
		glVertex2f(0.55,0.15);
		glVertex2f(0.45,0.85);
		glVertex2f(0.55,0.85);
		glVertex2f(0.55,0.15);
		glVertex2f(0.55,0.85);
		glVertex2f(0.45,0.15);
		glVertex2f(0.45,0.85);
	glEnd();

	glLoadIdentity();
	view->use3D(true);

	gluLookAt(2,2,2,	0,0,0,	0,1,0);
	glBegin(GL_LINES);
		glColor3f(1,0,0);
		glVertex3f(0,0,0);
		glVertex3f(1,0,0);
		glColor3f(0,1,0);
		glVertex3f(0,0,0);
		glVertex3f(0,1,0);
		glColor3f(0,0,1);
		glVertex3f(0,0,0);
		glVertex3f(0,0,1);
	glEnd();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glTranslatef(-1.25-1.25*currentTile,0.0,1.25+1.25*currentTile);
	vector<Tile*> *tiles = TileManager::Instance()->getTiles();
	for (int i=0; i<tiles->size(); i++) {
		glTranslatef(1.25,0,-1.25);
		glPushMatrix();
			glRotatef(rotate*90,0,1,0);
			glTranslatef(-0.5,0,-0.5);
			tiles[0][i]->drawTileSelection();
		glPopMatrix();
	}
}

void TileChooserWidget::wheelEvent(QWheelEvent *event)
{
	if (event->delta()>0)
		currentTile--;
	else if (event->delta()<0)
		currentTile++;
	if (currentTile < 0)
		currentTile = TileManager::Instance()->getTiles()->size() - 1;
	currentTile = currentTile % TileManager::Instance()->getTiles()->size();
	ArgoSceneManager::Instance()->getChunk()->setCurrentTile(TileManager::Instance()->getTiles()[0][currentTile]);
	this->repaint();
}

void TileChooserWidget::rotateTiles()
{
	rotate++;
	rotate = rotate % 4;
	this->repaint();
	ArgoSceneManager::Instance()->getChunk()->setCurrentRotate(rotate);
}