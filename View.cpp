#include "View.h"
#include "Matrix.h"
#include "MatrixManager.h"

void View::use3D(bool use3D)
{
    if (use3D)
	{
		MatrixManager::getInstance()->putMatrix4(PROJECTION, (glm::mat4) glm::perspective(fovy, aspect, zNear, zFar));
	}
    else
	{
		MatrixManager::getInstance()->putMatrix4(PROJECTION, (glm::mat4) glm::ortho(left, right, bottom, top, front, back));
	}
}

void View::set3D(GLdouble _fovy, GLdouble _aspect, GLdouble _zNear, GLdouble _zFar)
{
	fovy=_fovy;
    aspect=_aspect;
    zNear=_zNear;
    zFar=_zFar;
}

void View::set2D(GLdouble _left, GLdouble _right, GLdouble _bottom, GLdouble _top, GLdouble _front, GLdouble _back)
{
        left=_left;
        right=_right;
        bottom=_bottom;
        top=_top;
        front=_front;
        back=_back;
}

void View::viewport() 
{
	glViewport(0,0,width,height);
}

void View::viewport(int x, int y, int width, int height) 
{
	this->width = width; 
	this->height = height; 
	glViewport(x,y,width,height);
}

double View::getFOV() 
{
	return fovy;
}

double View::getAspect() 
{
	return aspect;
}

double View::getNear() 
{
	return zNear;
}

double View::getFar() 
{
	return zFar;
}

double View::getOrthoWidth() 
{
	return right-left;
}

double View::getOrthoHeight() 
{
	return top-bottom;
}

double View::getOrthoDepth() 
{
	return back-front;
}

double View::getOrthoNear()
{
	return front;
}

double View::getOrthoFar() 
{
	return back;
}