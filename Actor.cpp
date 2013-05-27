#include "Actor.h"
#include "MatrixManager.h"
#include "ShaderManager.h"
#include "MaterialManager.h"

Actor::Actor(string *sModel, string *sMaterial) : Transformable()
{
	this->m_psModel = sModel;
	this->m_psMaterial = sMaterial;
}

void Actor::drawActor(string sShader)
{
	GLSLProgram *glslProgram = gShaderManager->getShader(sShader);
	glslProgram->sendUniform("modelviewMatrix", &gMatrixManager->getMatrix4(MODELVIEW)[0][0]);
	if (sShader == "Basic" || sShader == "GBuffer") 
	{
		glslProgram->sendUniform("normalMatrix", &gMatrixManager->getMatrix3(NORMAL)[0][0],false,3);
		gMaterialManager->getMaterial(*m_psMaterial)->sendToShader(sShader);
	}
	gModelManager->getModel(*m_psModel)->draw();
}

float Actor::getScaledRadius()
{
	return gModelManager->getModel(*m_psModel)->getRadius()*max(max(m_nScale[0],m_nScale[1]),m_nScale[2]);
}

void Actor::setModel(string *sModel) 
{
	this->m_psModel = sModel;
}

string *Actor::getModel() 
{
	return m_psModel;
}

void Actor::setMaterial(string *sMaterial) 
{
	this->m_psMaterial = sMaterial;
}

string *Actor::getMaterial() 
{
	return m_psMaterial;
}