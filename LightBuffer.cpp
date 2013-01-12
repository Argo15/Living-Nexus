#include "LightBuffer.h"
#include "DrawFunc.h"
#include <assert.h>
#include "Logger.h"
#include "Profiler.h"
#include "GameState.h"
#include "ShaderManager.h"

LightBuffer::LightBuffer(int width, int height)
{
	this->width=width;
	this->height=height;

	glEnable(GL_TEXTURE_2D);

	glGenFramebuffersEXT(1,&buffer);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, buffer);

	glGenTextures(1, &lightTex);
	glBindTexture(GL_TEXTURE_2D, lightTex);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_FLOAT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, lightTex, 0);

	glGenTextures(1, &glowTex);
	glBindTexture(GL_TEXTURE_2D, glowTex);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_FLOAT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT1_EXT, GL_TEXTURE_2D, glowTex, 0);

	// check FbO status
	GLenum FBOstatus = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if(FBOstatus != GL_FRAMEBUFFER_COMPLETE_EXT)
		Logging::GRAPHICS->error("GL_FRAMEBUFFER_COMPLETE failed, CANNOT use FBO. " + FBOstatus);
	else
		Logging::GRAPHICS->info("Light Buffer Done");

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

void LightBuffer::drawToBuffer(GLuint normalTex, GLuint depthTex, GLuint glowTex, View *view)
{
	Profiler::getInstance()->startProfile("Draw Light");
	GLSLProgram *glslProgram = ShaderManager::getInstance()->getShader("DirectLight");
	glslProgram->use();

	bind();
	GLenum mrt[] = {GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT};
	glDrawBuffers(2, mrt);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushAttrib( GL_VIEWPORT_BIT );
	glViewport( 0, 0, getWidth(), getHeight());

	WorldState *worldState = (WorldState *) GameState::GAMESTATE;

	MatrixManager::getInstance()->putMatrix4(MODELVIEW, glm::mat4(1.0f));
	MatrixManager::getInstance()->putMatrix4(PROJECTION, glm::mat4(1.0f));
	Camera *camera = worldState->getPhysicsManager()->getWorldCameras()->getCurrentCamera();
	camera->transform();
	view->use3D(true);
	glm::mat4 invMVP = MatrixManager::getInstance()->getMatrix4(PROJECTION) * MatrixManager::getInstance()->getMatrix4(MODELVIEW);
	invMVP = glm::inverse(invMVP);
	MatrixManager::getInstance()->putMatrix4(MODELVIEW, glm::mat4(1.0f));
	MatrixManager::getInstance()->putMatrix4(PROJECTION, glm::mat4(1.0f));
	view->use3D(false);

	glBindFragDataLocation(glslProgram->getHandle(), 0, "lightBuffer");
	glBindFragDataLocation(glslProgram->getHandle(), 1, "glowBuffer");
	glBindAttribLocation(glslProgram->getHandle(), 0, "v_vertex");
	glBindAttribLocation(glslProgram->getHandle(), 1, "v_texture");

	worldState->getWorldManager()->getSun()->sendToShader("DirectLight");

	glslProgram->sendUniform("projectionMatrix", &MatrixManager::getInstance()->getMatrix4(PROJECTION)[0][0]);
	glslProgram->sendUniform("inverseMVPMatrix", &invMVP[0][0]);
	glslProgram->sendUniform("near", (float)view->getNear());
	glslProgram->sendUniform("far", (float)view->getFar());
	glslProgram->sendUniform("cameraPos",camera->geteyeX(),camera->geteyeY(),camera->geteyeZ());

	glActiveTexture(GL_TEXTURE0); 
	glBindTexture(GL_TEXTURE_2D, normalTex);
	glActiveTexture(GL_TEXTURE1); 
	glBindTexture(GL_TEXTURE_2D, depthTex);
	glActiveTexture(GL_TEXTURE2); 
	glBindTexture(GL_TEXTURE_2D, glowTex);
	glslProgram->sendUniform("normalTex",0);
	glslProgram->sendUniform("depthTex",1);
	glslProgram->sendUniform("glowTex",2);

	worldState->getShadowMapManager()->getSunShadow()->sendToShader("DirectLight");

	drawScreenShader(0,0,1.0f,1.0f);
	glslProgram->disable();
	unbind();	
	Profiler::getInstance()->endProfile();
}