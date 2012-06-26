#include <windows.h>
#undef __glext_h_
#undef __glxext_h_
#undef __gl_h_
#include <GL/GLee.h>

static void drawScreen(float x1, float y1, float x2, float y2)
{
	glBegin(GL_QUADS);
		glTexCoord2f(0,0);		 glVertex2f(x1,y1);
		glTexCoord2f(1.0f,0);	 glVertex2f(x2,y1);
		glTexCoord2f(1.0f,1.0f); glVertex2f(x2,y2);
		glTexCoord2f(0,1.0f);	 glVertex2f(x1,y2);
	glEnd();
}

static void drawScreenShader(float x1, float y1, float x2, float y2)
{
	glBegin(GL_QUADS);
		glVertexAttrib2f(1,0,0);		glVertexAttrib2f(0,x1,y1);
		glVertexAttrib2f(1,1.0f,0);		glVertexAttrib2f(0,x2,y1);
		glVertexAttrib2f(1,1.0f,1.0f);	glVertexAttrib2f(0,x2,y2);
		glVertexAttrib2f(1,0,1.0f);		glVertexAttrib2f(0,x1,y2);
	glEnd();
}