#include "WorldRenderer.h"
#include "WorldState.h"
#include "DrawFunc.h"
#include "GameState.h"
#include "RenderState.h"
#include "MatrixManager.h"
#include "ShaderManager.h"

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
	{
		h = 1;
	}
	GLfloat aspect = GLfloat(w) / h;
	view->viewport(0, 0, w, h);
	view->set3D(45.0f,aspect,0.01,50);
	view->set2D(0,1,0,1,0,1);
}

void WorldRenderer::forwardRender()
{
	MatrixManager::getInstance()->putMatrix4(MODELVIEW, glm::mat4(1.0f)); 
	MatrixManager::getInstance()->putMatrix4(PROJECTION, glm::mat4(1.0f)); 
	MatrixManager::getInstance()->putMatrix3(NORMAL, glm::mat3(1.0f)); 
	view->use3D(true);

	WorldState *worldState = (WorldState *) GameState::GAMESTATE;
	Camera *camera = worldState->getPhysicsManager()->getWorldCameras()->getCurrentCamera();
	camera->transform();
	GLSLProgram *glslProgram = ShaderManager::getInstance()->getShader("Basic");
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
	glslProgram->sendUniform("projectionMatrix", &MatrixManager::getInstance()->getMatrix4(PROJECTION)[0][0]);

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
	if (RenderStateManager::RENDERSTATE == FINAL)
	{
		motionBlurBuffer->bindBlurTex();
	}
	if (RenderStateManager::RENDERSTATE == POSITION)
	{
		gBuffer->bindPositionTex();
	}
	if (RenderStateManager::RENDERSTATE == NORMALMAP)	
	{
		gBuffer->bindNormalTex();
	}
	if (RenderStateManager::RENDERSTATE == COLOR)	
	{
		atmosphereBuffer->bindColorTex();
	}
	if (RenderStateManager::RENDERSTATE == LIGHTING)
	{
		lightBuffer->bindLightTex();
	}
	if (RenderStateManager::RENDERSTATE == SPECULAR)
	{
		lightBuffer->bindGlowTex();
	}
	if (RenderStateManager::RENDERSTATE == MOTION)	
	{
		gBuffer->bindMotionTex();
	}
	drawScreen(0.0,0.0,1.0,1.0);
}

void WorldRenderer::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	WorldState *worldState = (WorldState *) GameState::GAMESTATE;
	frustum->getFrustum(worldState->getPhysicsManager()->getWorldCameras()->getCurrentCamera(),view);
	
	if (RenderStateManager::RENDERSTATE == FORWARD)
	{
		forwardRender();
	}
	else
	{
		defferedRender();
	}

	glutSwapBuffers();
}

View *WorldRenderer::getView()
{	
	return view;
}
	
Frustum *WorldRenderer::getFrustum()
{
	return frustum;
}