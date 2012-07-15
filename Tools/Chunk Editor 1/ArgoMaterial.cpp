#include "ArgoMaterial.h"
#include <fstream>

ArgoMaterial::ArgoMaterial(QString *newName)
{
	for (int i=0;i<3;i++){
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
	name=newName;
	normalName=ArgoTextureManager::Instance()->getWhite()->getName();
	normalEnabled=false;
}

void ArgoMaterial::use(GLSLProgram *program)
{
	float spec[] = {specular, specular, specular};
	glDisable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,color);
	glMaterialfv(GL_FRONT,GL_AMBIENT,color);
	glMaterialfv(GL_FRONT,GL_SPECULAR,spec);
	glMaterialf(GL_FRONT,GL_SHININESS,shininess);
	glMaterialfv(GL_FRONT,GL_EMISSION,emission);
	glMatrixMode(GL_TEXTURE);
	glActiveTextureARB(GL_TEXTURE0);
	glLoadIdentity();
	glTranslatef(texOffset[0],texOffset[1],0.0);
	glRotatef(texRotate,0.0,0.0,1.0);
	glScalef(texScale[0],texScale[1],1.0);
	glMatrixMode(GL_MODELVIEW);

	if (program == 0) {
		glActiveTexture(GL_TEXTURE1); 
		glDisable(GL_TEXTURE_2D);
		glActiveTextureARB(GL_TEXTURE0);
		glEnable(GL_TEXTURE_2D);
		ArgoTextureManager::Instance()->BindTexture(*textureName);
	} else {
		glActiveTextureARB(GL_TEXTURE0);
		ArgoTextureManager::Instance()->BindTexture(*textureName);
		program->sendUniform("tex",0);
		glActiveTexture(GL_TEXTURE1); 
		ArgoTextureManager::Instance()->BindTexture(*normalName);
		program->sendUniform("normalmap",1);
		program->sendUniform("normalenabled",normalEnabled);
	}
}

void ArgoMaterial::saveMaterial(const char* filename) 
{
	SaveMat save;
	for (int i=0; i<3; i++) {
		save.color[i] = color[i];
		save.emission[i] = emission[i];
	}
	for (int i=0; i<2; i++) {
		save.texOffset[i] = texOffset[i];
		save.texScale[i] = texScale[i];
	}
	save.specular = specular;
	save.shininess = shininess;
	save.texRotate = texRotate;
	save.normalEnabled = normalEnabled;
	strcpy(save.name,qPrintable(*name));
	strcpy(save.textureName,qPrintable(*textureName));
	strcpy(save.normalName,qPrintable(*normalName));

	ofstream file(filename, ios::out|ios::binary|ios::ate);
	if (file.is_open())
	{ 
		file.write((char*)&save,sizeof(save));
	}
	file.close();
}

void ArgoMaterial::loadMaterial(const char* filename) 
{
	SaveMat load;

	ifstream file(filename, ios::in|ios::binary|ios::ate);
	if (file.is_open())
	{ 
		file.seekg (0, ios::beg);
		file.read((char*)&load,sizeof(load));
	} else { return; }
	file.close();

	for (int i=0; i<3; i++) {
		color[i] = load.color[i];
		emission[i] = load.emission[i];
	}
	for (int i=0; i<2; i++) {
		texOffset[i] = load.texOffset[i];
		texScale[i] = load.texScale[i];
	}
	specular = load.specular;
	shininess = load.shininess;
	texRotate = load.texRotate;
	normalEnabled = load.normalEnabled;

	name = new QString(load.name);
	textureName = new QString(load.textureName);
	normalName = new QString(load.normalName);
}