#ifndef ARGOGRAPHICSSETTINGS_H
#define ARGOGRAPHICSSETTINGS_H

#include <QGLWidget>
#include <QtGui>

class ArgoGraphicsSettings {
public:
    static ArgoGraphicsSettings* Instance();
    static void Initialize();

	bool shadersEnabled() {return shaders;}
	void setShadersEnabled(bool enabled) {shaders=enabled;}
	bool physicsEnabled() {return physics;}
	void setPhysicsEnabled(bool enabled) {physics=enabled;}

	int editMode;

private:
	bool shaders;
	bool physics;

	ArgoGraphicsSettings();
    static ArgoGraphicsSettings* pInstance;
};

#endif