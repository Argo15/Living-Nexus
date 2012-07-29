#include "MainGraphicsWidget.h"
#include "Matrix.h"
#include "NoState.h"
#include "QtCamera.h"
#include "SceneManager.h"
#include "FileWidget.h"
#include "DrawFunc.h"

MainGraphicsWidget::MainGraphicsWidget(QGLFormat fmt, QWidget *parent)
    : QGLWidget(fmt,parent) 
{
	fps = 60; // temp, unless it causes no problems
	setFormat(fmt);
	this->setMouseTracking(true);
	setFocusPolicy(Qt::StrongFocus);
	this->setAutoBufferSwap(true);
}

void MainGraphicsWidget::initializeGL() {
	Root::GAMESTATE = new NoState();
	Root::ModelviewMatrix.push(glm::mat4(1.0f)); 
	Root::ProjectionMatrix.push(glm::mat4(1.0f));
	Root::NormalMatrix.push(glm::mat3(1.0f));
	Root::inputManager = new InputManager();
	Root::textureManager = new TextureManager();
	Root::textureManager->Initialize();
	Root::modelManager = new ModelManager();
	Root::modelManager->Initialize();
	Root::materialManager = new MaterialManager();
	Root::materialManager->Initialize();
	Root::shaderManager = new ShaderManager();
	Root::shaderManager->Initialize();

	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
	glEnable(GL_NORMALIZE);
	glDisable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);

	view = new View();
	camera = new QtCamera();
	camera->setPosition(5,5,5);
	camera->setLookAt(0,0,0);
	camera->setUp(0,1,0);

	FileWidget::getInstance()->refresh();
	SceneManager::getInstance()->addTile("Tree");
	SceneManager::getInstance()->addChunk("Flat Chunk");

	myGrid = new grid(10, 10);
	myGrid->setColor(1.0, 1.0 ,1.0);
}

void MainGraphicsWidget::resizeGL(int width, int height) {
	if(height == 0)
		height = 1;
	GLfloat aspect = GLfloat(width) / height;
	view->viewport(0, 0, width, height);
	view->set3D(45.0f,aspect,0.01,50);
	view->set2D(0,1,0,1,0,1);
}

void MainGraphicsWidget::update(float fps) {
	camera->move(60/fps);
}

void MainGraphicsWidget::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Root::ModelviewMatrix.top() = glm::mat4(1.0f);
	Root::ProjectionMatrix.top() = glm::mat4(1.0f);
	Root::NormalMatrix.top() = glm::mat3(1.0f);
	view->use3D(true);

	camera->transform();
	GLSLProgram *glslProgram = Root::shaderManager->getShader("Basic");
	glslProgram->use();

	glBindFragDataLocation(glslProgram->getHandle(), 0, "fragColor");
	glBindAttribLocation(glslProgram->getHandle(), 0, "v_vertex");
	glBindAttribLocation(glslProgram->getHandle(), 1, "v_texture");
	glBindAttribLocation(glslProgram->getHandle(), 2, "v_normal");
	glBindAttribLocation(glslProgram->getHandle(), 3, "v_tangent");
	glBindAttribLocation(glslProgram->getHandle(), 4, "v_bitangent");

	glslProgram->sendUniform("light.direction", 1.0f,-5.0f,2.0f);
	glslProgram->sendUniform("light.color", 1.0f,1.0f,1.0f);
	glslProgram->sendUniform("light.ambient", 0.7f);
	glslProgram->sendUniform("light.diffuse", 0.6f);
	glslProgram->sendUniform("projectionMatrix", &Root::ProjectionMatrix.top()[0][0]);
	glslProgram->sendUniform("modelviewMatrix", &Root::ModelviewMatrix.top()[0][0]);
	glslProgram->sendUniform("curveGeometry", false);

	Root::materialManager->getMaterial("Default")->sendToShader("Basic");
	myGrid->draw();

	SceneManager::getInstance()->draw();

	glslProgram->disable();

	SceneManager::getInstance()->drawTransformers();
}


void MainGraphicsWidget::keyPressEvent (QKeyEvent *event) {
	Root::inputManager->registerKeyDown(event->key());
}

void MainGraphicsWidget::keyReleaseEvent (QKeyEvent *event) {
	Root::inputManager->registerKeyUp(event->key());
}

void MainGraphicsWidget::mousePressEvent(QMouseEvent *event) {
	int x = event->x();
	int y = event->y();
	if (event->buttons() & Qt::LeftButton) {
		if (Transformer::selected == -1)
			SceneManager::getInstance()->setSelectedActor(-1);
		Root::ModelviewMatrix.top() = glm::mat4(1.0f);
		Root::ProjectionMatrix.top() = glm::mat4(1.0f);
		view->use3D(true);
		camera->transform();
		Selection::calculateSelection(x,y);
	}
	Root::inputManager->registerMouseButtonDown(event->button());
}

void MainGraphicsWidget::mouseReleaseEvent(QMouseEvent *event) {
	Root::inputManager->registerMouseButtonUp(event->button());
}

void MainGraphicsWidget::mouseMoveEvent(QMouseEvent *event) {
	Root::ModelviewMatrix.top() = glm::mat4(1.0f);
	Root::ProjectionMatrix.top() = glm::mat4(1.0f);
	view->use3D(true);
	camera->transform();
	int x = event->x();
	int y = event->y();
	Root::inputManager->setMousePosition(x, y);
	if (event->buttons() & Qt::LeftButton){
		transformNoShaders();
		Transformer::calculateTransform(x,y,Root::inputManager->isSpecialKeyDown(Qt::Key_Shift),Root::inputManager->isSpecialKeyDown(Qt::Key_Control));
	} else {
		Selection::calculateSelectedTransformer(x,y);
		Transformer::dragPoint = Vector3(0.0);
	}
}

void MainGraphicsWidget::wheelEvent(QWheelEvent *event) {

}
	