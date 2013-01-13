#include "Material.h"
#include "TextureManager.h"
#include <fstream>

Material::Material()
	: Entity()
{
	for (int i=0;i<3;i++)
	{
		color[i]=1.0;
		emission[i]=0.0;
	}
	texOffset[0]=0.0;
	texOffset[1]=0.0;
	texScale[0]=1.0;
	texScale[1]=1.0;
	texRotate=0.0;
	specular=0.0;
	shininess=25;
	normalName=TextureManager::getInstance()->getTexture("White")->getName();
	normalEnabled=false;
}

void Material::use()
{
	float spec[] = {specular, specular, specular};
	glDisable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,color);
	glMaterialfv(GL_FRONT,GL_AMBIENT,color);
	glMaterialfv(GL_FRONT,GL_SPECULAR,spec);
	glMateriali(GL_FRONT,GL_SHININESS,shininess);
	glMaterialfv(GL_FRONT,GL_EMISSION,emission);
	glMatrixMode(GL_TEXTURE);
	glActiveTextureARB(GL_TEXTURE0);
	glLoadIdentity();
	glTranslatef(texOffset[0],texOffset[1],0.0);
	glRotatef(texRotate,0.0,0.0,1.0);
	glScalef(texScale[0],texScale[1],1.0);
	glMatrixMode(GL_MODELVIEW);

	glActiveTextureARB(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	TextureManager::getInstance()->BindTexture(*textureName);
}

void Material::sendToShader(string shader)
{
	GLSLProgram *glslProgram = ShaderManager::getInstance()->getShader(shader);
	glActiveTextureARB(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	TextureManager::getInstance()->BindTexture(*textureName);
	glActiveTextureARB(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);
	TextureManager::getInstance()->BindTexture(*normalName);
	glslProgram->sendUniform("tex", 0);
	glslProgram->sendUniform("normalmap", 1);
	glslProgram->sendUniform("material.normalenabled", normalEnabled);
	glslProgram->sendUniform("material.color", color[0],color[1],color[2]);
	if (shader == "GBuffer" || shader == "Basic")
	{
		glslProgram->sendUniform("material.emission", emission[0],emission[1],emission[2]);
		glslProgram->sendUniform("material.specular", specular);
		glslProgram->sendUniform("material.shininess", (float)shininess/128.0f);
	}
	glm::mat4 textureMatrix = glm::mat4(1.0f);
	textureMatrix = glm::translate(textureMatrix, glm::vec3(texOffset[0],texOffset[1],0));
	textureMatrix = glm::rotate(textureMatrix, texRotate, glm::vec3(0,0,1.0));
	textureMatrix = glm::scale(textureMatrix, glm::vec3(texScale[0],texScale[1],1.0));
	glslProgram->sendUniform("textureMatrix", &textureMatrix[0][0]);
}

bool Material::loadMaterial(const char* filename) 
{
	SaveMat load;

	ifstream file(filename, ios::in|ios::binary|ios::ate);
	if (file.is_open())
	{ 
		file.seekg (0, ios::beg);
		file.read((char*)&load,sizeof(load));
	} 
	else 
	{ 
		return false; 
	}
	file.close();

	for (int i=0; i<3; i++) 
	{
		color[i] = load.color[i];
		emission[i] = load.emission[i];
	}
	for (int i=0; i<2; i++) 
	{
		texOffset[i] = load.texOffset[i];
		texScale[i] = load.texScale[i];
	}
	specular = load.specular;
	shininess = load.shininess;
	texRotate = load.texRotate;
	normalEnabled = load.normalEnabled;

	name = new string(load.name);
	textureName = new string(load.textureName);
	normalName = new string(load.normalName);
	return true;
}

void Material::saveMaterial(const char *filename)
{
	SaveMat save;
	for (int i=0; i<3; i++) 
	{
		save.color[i] = color[i];
		save.emission[i] = emission[i];
	}
	for (int i=0; i<2; i++) 
	{
		save.texOffset[i] = texOffset[i];
		save.texScale[i] = texScale[i];
	}
	save.specular = specular;
	save.shininess = shininess;
	save.texRotate = texRotate;
	save.normalEnabled = normalEnabled;

	strcpy(save.name, name->c_str());
	strcpy(save.textureName, textureName->c_str());
	strcpy(save.normalName, normalName->c_str());

	ofstream file(filename, ios::out|ios::binary|ios::ate);
	if (file.is_open())
	{ 
		file.write((char*)&save,sizeof(save));
	}
	file.close();
}