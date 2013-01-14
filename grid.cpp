#include "Grid.h"

Grid::Grid()
{
	width=16;
	length=16;
	color[0]=0;
	color[1]=0;
	color[2]=0;
	center[0]=0;
	center[1]=0;
}

Grid::Grid(int l, int w)
{
	length=l;
	width=w;
	color[0]=0;
	color[1]=0;
	color[2]=0;
	center[0]=0;
	center[1]=0;
}

void Grid::setColor(float r, float g, float b)
{
	color[0]=r;
	color[1]=g;
	color[2]=b;
}

void Grid::setSize(int l, int w)
{
	length=l;
	width=w;
}

void Grid::setCenter(float x, float y)
{
	center[0]=x;
	center[1]=y;
}

void Grid::draw()
{
	float u = (float)width/2.0f;
	float v = (float)length/2.0f;
	glLineWidth(2.0);
	glVertexAttrib3f(2,0.0,0.0,0.0);
	glVertexAttrib3f(3,0.0,0.0,0.0);
	glVertexAttrib3f(4,0.0,0.0,0.0);
	//glVertexAttrib3f(5,color[0],color[1],color[2]);
	glColor3f(1.0,1.0,1.0);
	for (int x=0;x<=width;x++)
	{
			float a = center[0]-u+(float)x;
		for (float i=-v; i<v-0.1; i+=0.1)
		{
			glBegin(GL_LINES);
				glVertex3f(a,0,center[1]+i);
				glVertex3f(a,0,center[1]+i+0.1);
			glEnd();
		}
	}
	for (int y=0;y<=length;y++)
	{
		for (float i=-u; i<u-0.1; i+=0.1)
		{
			float b = center[1]-v+(float)y;
			glBegin(GL_LINES);
				glVertex3f(center[0]+i,0,b);
				glVertex3f(center[0]+i+0.1,0,b);
			glEnd();
		}
	}
	glLineWidth(1.0);
}