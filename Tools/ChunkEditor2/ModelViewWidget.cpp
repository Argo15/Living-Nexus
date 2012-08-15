#include "ModelViewWidget.h"

ModelViewWidget::ModelViewWidget(QWidget *parent, const QGLWidget *shareWidget)
 : QGLWidget(parent,shareWidget)
{
	setFocusPolicy(Qt::StrongFocus);
}

void ModelViewWidget::initializeGL()
{
	glShadeModel(GL_SMOOTH);				// GL_SMOOTH or GL_FLAT
	glClearDepth(1.0f);						// depth cleared to
	glEnable(GL_DEPTH_TEST);				// enable depth testing
	glEnable(GL_TEXTURE_2D);				// enable texturing
	glDepthFunc(GL_LEQUAL);					// lesser than or equal to depth
	
	view = new View();
	actor = new Actor(new std::string("Cube"), new std::string("Default"));

	camera = new QtCamera();
	camera->setLookAt(0,0,0);
	camera->setPosition(3,3,3);
	camera->setUp(0,1,0);
}

void ModelViewWidget::resizeGL(int width, int height)
{
	view->viewport(0,0,width,height);
	GLfloat aspect = GLfloat(width) / height;
	view->set3D(45.0f,aspect,0.1,100);
}

void ModelViewWidget::paintGL()
{
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

	glslProgram->sendUniform("light.direction", -5.0f,-5.0f,-5.0f);
	glslProgram->sendUniform("light.color", 1.0f,1.0f,1.0f);
	glslProgram->sendUniform("light.ambient", 0.7f);
	glslProgram->sendUniform("light.diffuse", 0.6f);
	glslProgram->sendUniform("projectionMatrix", &Root::ProjectionMatrix.top()[0][0]);
	glslProgram->sendUniform("modelviewMatrix", &Root::ModelviewMatrix.top()[0][0]);
	glslProgram->sendUniform("curveGeometry", false);

	glm::mat4 cameraInverse = glm::mat4(1.0);
	camera->transformToMatrix(&cameraInverse);
	cameraInverse = glm::inverse(cameraInverse);
	glslProgram->sendUniform("inverseCameraMatrix", &cameraInverse[0][0]);
	glslProgram->sendUniform("cameraPos", camera->geteyeX(), camera->geteyeY(), camera->geteyeZ());

	if (Root::materialManager->hasMaterial(*(actor->getMaterial())))
	{
		Root::ModelviewMatrix.push(Root::ModelviewMatrix.top());
		Root::NormalMatrix.push(Root::NormalMatrix.top());
			actor->transformToMatrix(&Root::ModelviewMatrix.top());
			actor->transformToMatrix(&Root::NormalMatrix.top());
			actor->drawActor("Basic");
		Root::ModelviewMatrix.pop();
		Root::NormalMatrix.pop();
	}

	glslProgram->disable();
}

void ModelViewWidget::setMaterial(std::string name)
{
	std::string *material = new string(name);
	actor->setMaterial(material);
	repaint();
}

void ModelViewWidget::setModel(std::string name)
{
	std::string *model = new std::string(name);
	actor->setModel(model);
	cameraDist=2.0 * actor->getScaledRadius();
	camera->setPosition(cameraDist,cameraDist,cameraDist);
	repaint();
}