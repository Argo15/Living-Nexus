#include "RelativeLayout.h"
#include "DrawFunc.h"

RelativeLayout::RelativeLayout(GuiElement *parent) : Layout(parent)
{

}

void RelativeLayout::drawChildren()
{
	glPushMatrix();
		for (int i=0; i<m_children->size(); i++)
		{
			GuiElement *child = (*m_children)[i];
			child->draw();
		}
	glPopMatrix();
}

// Handle onClick event, convert layout coordinates to children coordinates and call onclick on them
void RelativeLayout::onClick(int nButton, int nState, float nX, float nY)
{
	for (int i=0; i<m_children->size(); i++)
	{
		GuiElement *child = (*m_children)[i];
		float nChildClickX = (nX - child->getXPos()) / child->getWidth();
		float nChildClickY = (nY - child->getYPos()) / child->getHeight();
		float *nPadding = child->getPadding();
		if (nChildClickX >= nPadding[0] && nChildClickX <= (1.0f - nPadding[1])
			&& nChildClickY >= nPadding[2] && nChildClickY <= (1.0f - nPadding[3]))
		{
			child->onClick(nButton, nState, nChildClickX, nChildClickY);
		}
	}
}