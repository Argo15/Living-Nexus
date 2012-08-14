#include "TextureViewWidget.h"
#include "DrawFunc.h"

TextureViewWidget::TextureViewWidget(QWidget *parent, const QGLWidget *shareWidget)
 : QGLWidget(parent,shareWidget)
{
	setFocusPolicy(Qt::StrongFocus);
}

void TextureViewWidget::initializeGL()
{
	glShadeModel(GL_SMOOTH);				// GL_SMOOTH or GL_FLAT
	glClearDepth(1.0f);						// depth cleared to
	glEnable(GL_DEPTH_TEST);				// enable depth testing
	glEnable(GL_TEXTURE_2D);				// enable texturing
	glDepthFunc(GL_LEQUAL);					// lesser than or equal to depth

	view = new View();
	texture = "cobble";
}

void TextureViewWidget::resizeGL(int width, int height)
{
	view->viewport(0,0,width,height);
	view->set2D(0,1,0,1,0,1);
}

void TextureViewWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Root::ModelviewMatrix.top() = glm::mat4(1.0f);
	Root::ProjectionMatrix.top() = glm::mat4(1.0f);
	Root::NormalMatrix.top() = glm::mat3(1.0f);
	view->use3D(false);
	
	transformNoShaders();

	Root::textureManager->BindTexture(texture);
	drawScreen(0,0,1,1);
}

void TextureViewWidget::setTexture(std::string name)
{
	texture = name;
	repaint();
}