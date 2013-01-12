#include "AtmosphereBuffer.h"
#include "DrawFunc.h"
#include <assert.h>
#include "Logger.h"
#include "Profiler.h"
#include "GameState.h"
#include "MatrixManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"

static Vector3 DEFAULT_SKY_NEAR_COLOR(77, 153, 204);
static Vector3 DEFAULT_SKY_AWAY_COLOR(26, 52, 204);
static Vector3 DEFAULT_CLOUD_COLOR(255, 255, 255);

AtmosphereBuffer::AtmosphereBuffer(int width, int height)
{
	this->width=width;
	this->height=height;

	glEnable(GL_TEXTURE_2D);

	glGenFramebuffersEXT(1,&buffer);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, buffer);

	glGenTextures(1, &colorTex);
	glBindTexture(GL_TEXTURE_2D, colorTex);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_FLOAT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, colorTex, 0);

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
		Logging::GRAPHICS->info("Atmosphere Buffer Done");

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

void AtmosphereBuffer::drawToBuffer(GLuint colorBuf, GLuint glowBuf, GLuint depthBuf, View *view)
{
	Profiler::getInstance()->startProfile("Draw Atmosphere");
	GLSLProgram *glslProgram = ShaderManager::getInstance()->getShader("Atmosphere");
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

	glBindFragDataLocation(glslProgram->getHandle(), 0, "colorBuffer");
	glBindFragDataLocation(glslProgram->getHandle(), 1, "glowBuffer");
	glBindAttribLocation(glslProgram->getHandle(), 0, "v_vertex");
	glBindAttribLocation(glslProgram->getHandle(), 1, "v_texture");
	glslProgram->sendUniform("projectionMatrix", &MatrixManager::getInstance()->getMatrix4(PROJECTION)[0][0]);
	glslProgram->sendUniform("inverseMVPMatrix", &invMVP[0][0]);
	glslProgram->sendUniform("cameraPos",camera->geteyeX(),camera->geteyeY(),camera->geteyeZ());
	Vector3 sunDir = worldState->getWorldManager()->getSun()->getDirection();
	glslProgram->sendUniform("sunDir",sunDir[0],sunDir[1],sunDir[2]);
	glslProgram->sendUniform("nearSunColor",getNearSunColor()[0],getNearSunColor()[1],getNearSunColor()[2]);
	glslProgram->sendUniform("awaySunColor",getAwaySunColor()[0],getAwaySunColor()[1],getAwaySunColor()[2]);
	glslProgram->sendUniform("cloudColor",getCloudColor()[0],getCloudColor()[1],getCloudColor()[2]);

	glActiveTexture(GL_TEXTURE0); 
	glBindTexture(GL_TEXTURE_2D, colorBuf);
	glActiveTexture(GL_TEXTURE1); 
	glBindTexture(GL_TEXTURE_2D, glowBuf);
	glActiveTexture(GL_TEXTURE2); 
	glBindTexture(GL_TEXTURE_2D, depthBuf);
	glActiveTexture(GL_TEXTURE3); 
	TextureManager::getInstance()->BindTexture("Cloud");
	glslProgram->sendUniform("colorTex",0);
	glslProgram->sendUniform("glowTex",1);
	glslProgram->sendUniform("depthTex",2);
	glslProgram->sendUniform("cloudTex",3);
	glslProgram->sendUniform("near", (float)view->getNear());
	glslProgram->sendUniform("far", (float)view->getFar());

	drawScreenShader(0,0,1.0f,1.0f);
	glslProgram->disable();
	unbind();	
	Profiler::getInstance()->endProfile();
}

Vector3 AtmosphereBuffer::getNearSunColor()
{
	float timeWeights[] = {
		getWeightForTimeOfDay(TimeUtils::TimeOfDay::MORNING),
		getWeightForTimeOfDay(TimeUtils::TimeOfDay::DAY),
		getWeightForTimeOfDay(TimeUtils::TimeOfDay::EVENING),
		getWeightForTimeOfDay(TimeUtils::TimeOfDay::NIGHT)
	};
	Vector3 timeColors[] = {
		getSkyNearSunColor(TimeUtils::TimeOfDay::MORNING),
		getSkyNearSunColor(TimeUtils::TimeOfDay::DAY),
		getSkyNearSunColor(TimeUtils::TimeOfDay::EVENING),
		getSkyNearSunColor(TimeUtils::TimeOfDay::NIGHT)
	};
	Vector3 vColor(0);
	for (int i=0; i<4; i++) {
		vColor = vColor + timeColors[i] * timeWeights[i];
	}
	return vColor;
}

Vector3 AtmosphereBuffer::getAwaySunColor()
{
	float timeWeights[] = {
		getWeightForTimeOfDay(TimeUtils::TimeOfDay::MORNING),
		getWeightForTimeOfDay(TimeUtils::TimeOfDay::DAY),
		getWeightForTimeOfDay(TimeUtils::TimeOfDay::EVENING),
		getWeightForTimeOfDay(TimeUtils::TimeOfDay::NIGHT)
	};
	Vector3 timeColors[] = {
		getSkyAwaySunColor(TimeUtils::TimeOfDay::MORNING),
		getSkyAwaySunColor(TimeUtils::TimeOfDay::DAY),
		getSkyAwaySunColor(TimeUtils::TimeOfDay::EVENING),
		getSkyAwaySunColor(TimeUtils::TimeOfDay::NIGHT)
	};
	Vector3 vColor(0);
	for (int i=0; i<4; i++) {
		vColor = vColor + timeColors[i] * timeWeights[i];
	}
	return vColor;
}

Vector3 AtmosphereBuffer::getCloudColor()
{
	float timeWeights[] = {
		getWeightForTimeOfDay(TimeUtils::TimeOfDay::MORNING),
		getWeightForTimeOfDay(TimeUtils::TimeOfDay::DAY),
		getWeightForTimeOfDay(TimeUtils::TimeOfDay::EVENING),
		getWeightForTimeOfDay(TimeUtils::TimeOfDay::NIGHT)
	};
	Vector3 timeColors[] = {
		TimeUtils::getCloudColor(TimeUtils::TimeOfDay::MORNING),
		TimeUtils::getCloudColor(TimeUtils::TimeOfDay::DAY),
		TimeUtils::getCloudColor(TimeUtils::TimeOfDay::EVENING),
		TimeUtils::getCloudColor(TimeUtils::TimeOfDay::NIGHT)
	};
	Vector3 vColor(0);
	for (int i=0; i<4; i++) {
		vColor = vColor + timeColors[i] * timeWeights[i];
	}
	return vColor;
}