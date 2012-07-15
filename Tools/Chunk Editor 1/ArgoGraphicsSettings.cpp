#include "ArgoGraphicsSettings.h"

ArgoGraphicsSettings *ArgoGraphicsSettings::pInstance = 0;

ArgoGraphicsSettings::ArgoGraphicsSettings()
{
	shaders = true;
	physics = true;
	editMode = 0;
}

void ArgoGraphicsSettings::Initialize()
{
	pInstance=new ArgoGraphicsSettings;
}

ArgoGraphicsSettings *ArgoGraphicsSettings::Instance()
{
	return pInstance;
}