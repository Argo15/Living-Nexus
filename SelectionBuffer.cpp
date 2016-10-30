#include "SelectionBuffer.h"
#include "DrawFunc.h"
#include "Logger.h"
#include "Profiler.h"
#include "GameState.h"
#include "ShaderManager.h"
#include "ModelManager.h"
#include "StringUtils.h"

void SelectionBuffer::getColorFromID(int id, float *color)
{
	color[0]=(float)(id%255)/255.0;
	color[1]=(float)((id/255)%255)/255.0;
	color[2]=(float)((id/(255*255))%255)/255.0;
}

int SelectionBuffer::getIDFromColor(float r, float g, float b)
{
	int iR = (int)(r);
	int iG = (int)(g);
	int ib = (int)(b);
	int selectID = iR+iG*255+ib*255*255;
	return selectID;
}

SelectionBuffer::SelectionBuffer(int nWidth, int nHeight)
{
	this->m_nWidth=nWidth;
	this->m_nHeight=nHeight;

	glEnable(GL_TEXTURE_2D);

	glGenFramebuffersEXT(1,&m_nFrameBuffer);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_nFrameBuffer);

	glGenTextures(1, &m_nSelectionTex);
	glBindTexture(GL_TEXTURE_2D, m_nSelectionTex);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_nWidth, m_nHeight, 0, GL_RGBA, GL_FLOAT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, m_nSelectionTex, 0);

	// check FbO status
	GLenum FBOstatus = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if(FBOstatus != GL_FRAMEBUFFER_COMPLETE_EXT)
	{
		Logging::GRAPHICS->error("GL_FRAMEBUFFER_COMPLETE failed, CANNOT use FBO. " + FBOstatus);
	}
	else
	{
		Logging::GRAPHICS->info("Selection Buffer Done");
	}

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

SelectionBuffer::~SelectionBuffer()
{
	glDeleteFramebuffers(1,&m_nFrameBuffer);
}

void SelectionBuffer::drawToBuffer(vector<ClickObject *> *clickObjects, View *view, Camera *camera)
{
	gProfiler->startProfile("Draw Selection");
	GLSLProgram *glslProgram = gShaderManager->getShader("Selection");
	glslProgram->use();

	bind();
	glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushAttrib( GL_VIEWPORT_BIT );
	glViewport( 0, 0, getWidth(), getHeight());

	gMatrixManager->putMatrix4(MODELVIEW, glm::mat4(1.0f));
	gMatrixManager->putMatrix4(PROJECTION, glm::mat4(1.0f));
	view->use3D(true);
	gMatrixManager->putMatrix4(PROJECTION, camera->transformToMatrix(gMatrixManager->getMatrix4(PROJECTION)));

	glBindFragDataLocation(glslProgram->getHandle(), 0, "selectionBuffer");
	glBindAttribLocation(glslProgram->getHandle(), 0, "v_vertex");

	glslProgram->sendUniform("projectionCameraMatrix", &gMatrixManager->getMatrix4(PROJECTION)[0][0]);
	glslProgram->sendUniform("camPos",camera->getEyeX(),camera->getEyeY(),camera->getEyeZ());

	int nId=1;
	for (std::vector<ClickObject *>::iterator it = clickObjects->begin(); it != clickObjects->end(); it++)
	{
		gMatrixManager->pushMatrix4(MODELVIEW);
			gMatrixManager->multMatrix4(MODELVIEW, (*it)->getTransform());
			glslProgram->sendUniform("modelviewMatrix", &gMatrixManager->getMatrix4(MODELVIEW)[0][0]);
			float nColor[3];
			getColorFromID(nId, nColor);
			glslProgram->sendUniform("color", nColor[0], nColor[1], nColor[2]);
			(*it)->getTile()->drawTile("Selection");
		gMatrixManager->popMatrix4(MODELVIEW);
		nId++;
	}

	unsigned char color[4];
	glReadPixels(m_nWidth/2, m_nHeight/2, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
	m_nSelectedId = getIDFromColor(color[0], color[1], color[2])-1;

	glslProgram->disable();
	unbind();	
	gProfiler->endProfile();
}

void SelectionBuffer::bind() 
{
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_nFrameBuffer);
}

void SelectionBuffer::unbind() 
{
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

void SelectionBuffer::bindSelectionTex() 
{
	glBindTexture(GL_TEXTURE_2D, m_nSelectionTex);
}

GLuint SelectionBuffer::getSelectionTex() 
{
	return m_nSelectionTex;
}

int SelectionBuffer::getWidth() 
{
	return m_nWidth;
}

int SelectionBuffer::getHeight() 
{
	return m_nHeight;
}

int SelectionBuffer::getSelectedObject()
{
	return m_nSelectedId;
}