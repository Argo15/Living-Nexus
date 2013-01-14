#include "Transformable.h"

Transformable::Transformable()
{
	for (int i=0;i<3;i++)
	{
		translations[i]=0;
		scale[i]=1.0;
	}
	rotation = Quaternion();
}

void Transformable::transform()
{
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(translations[0],translations[1],translations[2]);
	rotation.getMatrix().multiplyToCurrent();
	glScalef(scale[0],scale[1],scale[2]);
}

glm::mat4 Transformable::transformToMatrix(glm::mat4 matrix)
{
	glm::mat4 mat = glm::mat4(1.0f);
	mat = glm::translate(mat, glm::vec3(translations[0],translations[1],translations[2]));
	glm::quat rot = glm::quat(rotation[0],rotation[1],rotation[2],rotation[3]);
	mat = mat * glm::mat4_cast(rot);
	mat = glm::scale(mat, glm::vec3(scale[0],scale[1],scale[2]));
	return matrix * mat;
}

glm::mat3 Transformable::transformToMatrix(glm::mat3 matrix)
{
	glm::mat3 mat = glm::mat3(1.0f);
	glm::quat rot = glm::quat(rotation[0],rotation[1],rotation[2],rotation[3]);
	mat = mat * glm::mat3_cast(rot);
	return matrix * mat;
}

void Transformable::Translate(float x, float y, float z) 
{
	translations[0]+=x;
	translations[1]+=y;
	translations[2]+=z;
}

void Transformable::Rotate(Quaternion quat) 
{
	rotation=quat*rotation;
}

void Transformable::Scale(float x, float y, float z) 
{
	scale[0]+=x;
	scale[1]+=y;
	scale[2]+=z;
}

void Transformable::setTranslate(float x, float y, float z) 
{
	translations[0]=x;
	translations[1]=y;
	translations[2]=z;
}

void Transformable::setRotate(Quaternion quat) 
{
	rotation = quat;
}

void Transformable::setScale(float x, float y, float z) 
{
	scale[0]=x;
	scale[1]=y;
	scale[2]=z;
}

float *Transformable::getTranslate() 
{
	float *pTranslate = translations; 
	return pTranslate;
}

Quaternion Transformable::getRotate() 
{
	return rotation;
}

float *Transformable::getScale() 
{
	float *pScale;
	pScale=scale; 
	return pScale;
}

Vector3 Transformable::getTranslateV() 
{
	return Vector3(translations[0],translations[1],translations[2]);
}