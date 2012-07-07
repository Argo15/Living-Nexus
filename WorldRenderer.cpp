#include "WorldRenderer.h"
#include "WorldState.h"
#include "DrawFunc.h"

WorldRenderer::WorldRenderer()
{
}

void WorldRenderer::init()
{
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_CULL_FACE);

	view = new View();
	camera = new WorldCamera();
	frustum = new Frustum();

	gBuffer = new GBuffer(1280,720);
	atmosphereBuffer = new AtmosphereBuffer(1280,720);
	lightBuffer = new LightBuffer(1280,720);
	finalBuffer = new FinalBuffer(1280,720);
	motionBlurBuffer = new MotionBlurBuffer(1280,720);
}

void WorldRenderer::resize(int w, int h)
{
	if(h == 0)
		h = 1;
	GLfloat aspect = GLfloat(w) / h;
	view->viewport(0, 0, w, h);
	view->set3D(45.0f,aspect,0.01,50);
	view->set2D(0,1,0,1,0,1);
}

void WorldRenderer::forwardRender()
{
	Root::ModelviewMatrix.top() = glm::mat4(1.0f);
	Root::ProjectionMatrix.top() = glm::mat4(1.0f);
	Root::NormalMatrix.top() = glm::mat3(1.0f);
	view->use3D(true);

	WorldState *worldState = (WorldState *) Root::GAMESTATE;
	Camera *camera = worldState->getPhysicsManager()->getWorldCameras()->getCurrentCamera();
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

	worldState->getWorldManager()->renderWorld("Basic");

	glslProgram->disable();
}

void WorldRenderer::defferedRender()
{
	gBuffer->drawToBuffer(view);
	atmosphereBuffer->drawToBuffer(gBuffer->getColorTex(), gBuffer->getGlowTex(), gBuffer->getDepthTex(), view);
	lightBuffer->drawToBuffer(gBuffer->getNormalTex(), gBuffer->getDepthTex(), atmosphereBuffer->getGlowTex(), view);
	finalBuffer->drawToBuffer(atmosphereBuffer->getColorTex(), lightBuffer->getLightTex(), lightBuffer->getGlowTex(), view);
	motionBlurBuffer->drawToBuffer(finalBuffer->getFinalTex(), gBuffer->getMotionTex(), 10, view);

	glDisable(GL_LIGHTING);
	glActiveTextureARB(GL_TEXTURE2);
	glDisable(GL_TEXTURE_2D);
	glActiveTextureARB(GL_TEXTURE1);
	glDisable(GL_TEXTURE_2D);
	glActiveTextureARB(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);

	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1.0, 0, 1.0);
	view->viewport();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	
	glBindTexture(GL_TEXTURE_2D, 0);
	if (Root::RENDERSTATE == FINAL)		motionBlurBuffer->bindBlurTex();
	if (Root::RENDERSTATE == POSITION)	gBuffer->bindPositionTex();
	if (Root::RENDERSTATE == NORMAL)	gBuffer->bindNormalTex();
	if (Root::RENDERSTATE == COLOR)		atmosphereBuffer->bindColorTex();
	if (Root::RENDERSTATE == LIGHTING)	lightBuffer->bindLightTex();
	if (Root::RENDERSTATE == SPECULAR)	lightBuffer->bindGlowTex();
	if (Root::RENDERSTATE == MOTION)	gBuffer->bindMotionTex();
	drawScreen(0.0,0.0,1.0,1.0);
}

void WorldRenderer::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	WorldState *worldState = (WorldState *) Root::GAMESTATE;
	frustum->getFrustum(worldState->getPhysicsManager()->getWorldCameras()->getCurrentCamera(),view);
	
	if (Root::RENDERSTATE == FORWARD) {
		forwardRender();
	} else {
		defferedRender();
	}

	glutSwapBuffers();
}