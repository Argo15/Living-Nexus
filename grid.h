#ifndef GRID_H
#define GRID_H

#include <windows.h>
#undef __glext_h_
#undef __glxext_h_
#undef __gl_h_
#include <GL/GLee.h>

class Grid{
private:
	float color[3];
	int length,width;
	float center[2];
public:
	Grid();
	Grid(int l, int w);

	void setColor(float r, float g, float b);
	void setSize(int l, int w);
	void setCenter(float x, float y);
	void draw();
};
#endif
