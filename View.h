#ifndef VIEW_H
#define VIEW_H

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

class View
{
private:
	double fovy, aspect, zNear, zFar;
	double left, right, top, bottom, front, back;
	int width, height;

public:
	void use3D(bool use3D);
	void set3D(GLdouble _fovy, GLdouble _aspect, GLdouble _zNear, GLdouble _zFar);
	void set2D(GLdouble _left, GLdouble _right, GLdouble _bottom, GLdouble _top, GLdouble front, GLdouble back);
	void viewport();
	void viewport(int x, int y, int width, int height);
	double getFOV();
	double getAspect();
	double getNear();
	double getFar();
	double getOrthoWidth();
	double getOrthoHeight();
	double getOrthoDepth();
	double getOrthoNear();
	double getOrthoFar();
};

#endif