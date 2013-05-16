#include "WorldRenderer.h"
#include "WorldState.h"
#include "DrawFunc.h"
#include "GameState.h"
#include "RenderState.h"
#include "MatrixManager.h"
#include "ShaderManager.h"
#include "HorizontalLayout.h"
#include "VerticalLayout.h"
#include "GuiManager.h"
#include "FreeTypeManager.h"
#include "ClickManager.h"

static int N_FRAME_WIDTH = 1280;
static int N_FRAME_HEIGHT = 720;

WorldRenderer::WorldRenderer()
{

}

/*
 * Initialize Opengl and Frame Buffer Objects.
 */
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

	m_view = new View();
	m_frustum = new Frustum();

	m_gBuffer = new GBuffer(N_FRAME_WIDTH,N_FRAME_HEIGHT);
	m_atmosphereBuffer = new AtmosphereBuffer(N_FRAME_WIDTH,N_FRAME_HEIGHT);
	m_lightBuffer = new LightBuffer(N_FRAME_WIDTH,N_FRAME_HEIGHT);
	m_finalBuffer = new FinalBuffer(N_FRAME_WIDTH,N_FRAME_HEIGHT);
	m_motionBlurBuffer = new MotionBlurBuffer(N_FRAME_WIDTH,N_FRAME_HEIGHT);
}

/*
 * Resize: change the view to reflect the new width and height.
 */
void WorldRenderer::resize(int nWidth, int nHeight)
{
	if(nHeight == 0)
	{
		nHeight = 1;
	}
	GLfloat nAspect = GLfloat(nWidth) / nHeight;
	m_view->viewport(0, 0, nWidth, nHeight);
	m_view->set3D(45.0f,nAspect,0.01,50);
	m_view->set2D(0,1,0,1,0,1);
}

/*
 * Render the world using simple shaders.
 */
void WorldRenderer::forwardRender()
{
	MatrixManager::getInstance()->putMatrix4(MODELVIEW, glm::mat4(1.0f)); 
	MatrixManager::getInstance()->putMatrix4(PROJECTION, glm::mat4(1.0f)); 
	MatrixManager::getInstance()->putMatrix3(NORMAL, glm::mat3(1.0f)); 
	m_view->use3D(true);

	WorldState *worldState = (WorldState *) GameState::GAMESTATE;
	Camera *m_camera = worldState->getPhysicsManager()->getWorldCameras()->getCurrentCamera();
	m_camera->transform();
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

/*
 * Render the world using deffered shading. This involves rendering
 * the positions, color, normals, and velocity to a "G-Buffer", then using
 * this data to render lighting, motion blur, etc.
 */
void WorldRenderer::defferedRender()
{
	m_gBuffer->drawToBuffer(m_view);
	m_atmosphereBuffer->drawToBuffer(m_gBuffer->getColorTex(), m_gBuffer->getGlowTex(), m_gBuffer->getDepthTex(), m_view);
	m_lightBuffer->drawToBuffer(m_gBuffer->getNormalTex(), m_gBuffer->getDepthTex(), m_atmosphereBuffer->getGlowTex(), m_view);
	m_finalBuffer->drawToBuffer(m_atmosphereBuffer->getColorTex(), m_lightBuffer->getLightTex(), m_lightBuffer->getGlowTex(), m_view);
	m_motionBlurBuffer->drawToBuffer(m_finalBuffer->getFinalTex(), m_gBuffer->getMotionTex(), 15, m_view);

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
	m_view->viewport();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	
	glBindTexture(GL_TEXTURE_2D, 0);
	if (RenderStateManager::RENDERSTATE == FINAL)
	{
		m_motionBlurBuffer->bindBlurTex();
	}
	if (RenderStateManager::RENDERSTATE == POSITION)
	{
		m_gBuffer->bindPositionTex();
		ClickManager::getInstance()->getSelectionBuffer()->bindSelectionTex();
	}
	if (RenderStateManager::RENDERSTATE == NORMALMAP)	
	{
		m_gBuffer->bindNormalTex();
	}
	if (RenderStateManager::RENDERSTATE == COLOR)	
	{
		m_atmosphereBuffer->bindColorTex();
	}
	if (RenderStateManager::RENDERSTATE == LIGHTING)
	{
		m_lightBuffer->bindLightTex();
	}
	if (RenderStateManager::RENDERSTATE == SPECULAR)
	{
		m_lightBuffer->bindGlowTex();
	}
	if (RenderStateManager::RENDERSTATE == MOTION)	
	{
		m_gBuffer->bindMotionTex();
	}
	drawScreen(0.0,0.0,1.0,1.0);
}

/*
 * Render the world.
 */
void WorldRenderer::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	WorldState *worldState = (WorldState *) GameState::GAMESTATE;
	Camera *camera = worldState->getPhysicsManager()->getWorldCameras()->getCurrentCamera();
	m_frustum->getFrustum(camera,m_view);
	ClickManager::getInstance()->setView(m_view);
	ClickManager::getInstance()->setCamera(camera);

	// Draw world
	if (RenderStateManager::RENDERSTATE == FORWARD)
	{
		forwardRender();
	}
	else
	{
		defferedRender();
	}

	// Draw gui
	m_view->use3D(false);
	GuiManager::getInstance()->render();

	glutSwapBuffers();
}

View *WorldRenderer::getView()
{	
	return m_view;
}
	
Frustum *WorldRenderer::getFrustum()
{
	return m_frustum;
}