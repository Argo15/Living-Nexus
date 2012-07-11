#include "AtmosphereBuffer.h"
#include "DrawFunc.h"
#include <assert.h>

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
		printf("GL_FRAMEBUFFER_COMPLETE failed, CANNOT use FBO. %i\n",FBOstatus);
	else
		printf("Atmosphere Buffer Done\n");

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

void AtmosphereBuffer::drawToBuffer(GLuint colorBuf, GLuint glowBuf, GLuint depthBuf, View *view)
{
	GLSLProgram *glslProgram = Root::shaderManager->getShader("Atmosphere");
	glslProgram->use();

	bind();
	GLenum mrt[] = {GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT};
	glDrawBuffers(2, mrt);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushAttrib( GL_VIEWPORT_BIT );
	glViewport( 0, 0, getWidth(), getHeight());

	WorldState *worldState = (WorldState *) Root::GAMESTATE;

	Root::ModelviewMatrix.top() = glm::mat4(1.0f);
	Root::ProjectionMatrix.top() = glm::mat4(1.0f);
	Camera *camera = worldState->getPhysicsManager()->getWorldCameras()->getCurrentCamera();
	camera->transform();
	view->use3D(true);
	glm::mat4 invMVP = Root::ProjectionMatrix.top() * Root::ModelviewMatrix.top();
	invMVP = glm::inverse(invMVP);
	Root::ModelviewMatrix.top() = glm::mat4(1.0f);
	Root::ProjectionMatrix.top() = glm::mat4(1.0f);
	view->use3D(false);

	glBindFragDataLocation(glslProgram->getHandle(), 0, "colorBuffer");
	glBindFragDataLocation(glslProgram->getHandle(), 1, "glowBuffer");
	glBindAttribLocation(glslProgram->getHandle(), 0, "v_vertex");
	glBindAttribLocation(glslProgram->getHandle(), 1, "v_texture");
	glslProgram->sendUniform("projectionMatrix", &Root::ProjectionMatrix.top()[0][0]);
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
	Root::textureManager->BindTexture("Cloud");
	glslProgram->sendUniform("colorTex",0);
	glslProgram->sendUniform("glowTex",1);
	glslProgram->sendUniform("depthTex",2);
	glslProgram->sendUniform("cloudTex",3);
	glslProgram->sendUniform("near", (float)view->getNear());
	glslProgram->sendUniform("far", (float)view->getFar());

	drawScreenShader(0,0,1.0f,1.0f);
	glslProgram->disable();
	unbind();	
}

Vector3 AtmosphereBuffer::getNearSunColor()
{
	float timeWeights[] = {
		getWeightForTimeOfDay(Time::TimeOfDay::MORNING),
		getWeightForTimeOfDay(Time::TimeOfDay::DAY),
		getWeightForTimeOfDay(Time::TimeOfDay::EVENING),
		getWeightForTimeOfDay(Time::TimeOfDay::NIGHT)
	};
	Vector3 timeColors[] = {
		getSkyNearSunColor(Time::TimeOfDay::MORNING),
		getSkyNearSunColor(Time::TimeOfDay::DAY),
		getSkyNearSunColor(Time::TimeOfDay::EVENING),
		getSkyNearSunColor(Time::TimeOfDay::NIGHT)
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
		getWeightForTimeOfDay(Time::TimeOfDay::MORNING),
		getWeightForTimeOfDay(Time::TimeOfDay::DAY),
		getWeightForTimeOfDay(Time::TimeOfDay::EVENING),
		getWeightForTimeOfDay(Time::TimeOfDay::NIGHT)
	};
	Vector3 timeColors[] = {
		getSkyAwaySunColor(Time::TimeOfDay::MORNING),
		getSkyAwaySunColor(Time::TimeOfDay::DAY),
		getSkyAwaySunColor(Time::TimeOfDay::EVENING),
		getSkyAwaySunColor(Time::TimeOfDay::NIGHT)
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
		getWeightForTimeOfDay(Time::MORNING),
		getWeightForTimeOfDay(Time::DAY),
		getWeightForTimeOfDay(Time::EVENING),
		getWeightForTimeOfDay(Time::NIGHT)
	};
	Vector3 timeColors[] = {
		Time::getCloudColor(Time::MORNING),
		Time::getCloudColor(Time::DAY),
		Time::getCloudColor(Time::EVENING),
		Time::getCloudColor(Time::NIGHT)
	};
	Vector3 vColor(0);
	for (int i=0; i<4; i++) {
		vColor = vColor + timeColors[i] * timeWeights[i];
	}
	return vColor;
}