#include "SquareFrame.h"
#include "DrawFunc.h"
#include "Logger.h"

SquareFrame::SquareFrame(GuiElement *parent) : RelativeLayout(parent)
{

}


void SquareFrame::initialize(View *view)
{
	float nAspect = view->getAspect();
	if (nAspect > 1.0f)
	{
		nHeight = 1.0f;
		nWidth = nAspect;
	}
	else
	{
		nHeight = 1.0f/nAspect;
		nWidth = 1.0f;
	}
}

void SquareFrame::drawChildren()
{
	glPushMatrix();
		glScalef(1.0f/nWidth, 1.0f/nHeight, 0);
		glTranslatef((nWidth-1.0f)/2.0f, (nHeight-1.0f)/2.0f, 0);
		RelativeLayout::drawChildren();
	glPopMatrix();
}

// Handle onClick event, convert layout coordinates to children coordinates and call onclick on them
void SquareFrame::onClick(int nButton, int nState, float nX, float nY)
{
	float nScaledX = nX * nWidth - (nWidth-1.0f)/2.0f;
	float nScaledY = nY * nHeight - (nHeight-1.0f)/2.0f;
	RelativeLayout::onClick(nButton, nState, nScaledX, nScaledY);
}