#include "MotionBlurBuffer.h"
#include "DrawFunc.h"
#include <assert.h>
#include "Logger.h"
#include "Profiler.h"
#include "GameState.h"
#include "ShaderManager.h"

MotionBlurBuffer::MotionBlurBuffer(int width, int height)
{
	this->width=width;
	this->height=height;

	glEnable(GL_TEXTURE_2D);

	glGenFramebuffersEXT(1,&buffer);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, buffer);

	glGenTextures(1, &blurTex);
	glBindTexture(GL_TEXTURE_2D, blurTex);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_FLOAT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, blurTex, 0);

	// check FbO status
	GLenum FBOstatus = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if(FBOstatus != GL_FRAMEBUFFER_COMPLETE_EXT)
		Logging::GRAPHICS->error("GL_FRAMEBUFFER_COMPLETE failed, CANNOT use FBO. " + FBOstatus);
	else
		Logging::GRAPHICS->info("Motion Blur Buffer Done");

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

void MotionBlurBuffer::drawToBuffer(GLuint texture, GLuint velocityTex, int numSamples, View *view)
{
	Profiler::getInstance()->startProfile("Draw Motion Blur");
	GLSLProgram *glslProgram = ShaderManager::getInstance()->getShader("MotionBlur");
	glslProgram->use();

	bind();
	glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushAttrib( GL_VIEWPORT_BIT );
	glViewport( 0, 0, getWidth(), getHeight());

	WorldState *worldState = (WorldState *) GameState::GAMESTATE;

	MatrixManager::getInstance()->putMatrix4(MODELVIEW, glm::mat4(1.0f));
	MatrixManager::getInstance()->putMatrix4(PROJECTION, glm::mat4(1.0f));
	view->use3D(false);

	glBindFragDataLocation(glslProgram->getHandle(), 0, "blurBuffer");
	glBindAttribLocation(glslProgram->getHandle(), 0, "v_vertex");
	glBindAttribLocation(glslProgram->getHandle(), 1, "v_texture");

	glslProgram->sendUniform("projectionMatrix", &MatrixManager::getInstance()->getMatrix4(PROJECTION)[0][0]);

	glActiveTexture(GL_TEXTURE0); 
	glBindTexture(GL_TEXTURE_2D, texture);
	glActiveTexture(GL_TEXTURE1); 
	glBindTexture(GL_TEXTURE_2D, velocityTex);
	glslProgram->sendUniform("tex",0);
	glslProgram->sendUniform("velTex",1);
	glslProgram->sendUniform("numSamples",15.0f);

	drawScreenShader(0,0,1.0f,1.0f);
	glslProgram->disable();
	unbind();	
	Profiler::getInstance()->endProfile();
}