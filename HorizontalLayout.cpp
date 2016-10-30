#include "HorizontalLayout.h"
#include "DrawFunc.h"
#include "Logger.h"

HorizontalLayout::HorizontalLayout(GuiElement *parent) : Layout(parent)
{

}

void HorizontalLayout::drawChildren()
{
	for (int i=0; i<m_children->size(); i++)
	{
		GuiElement *child = (*m_children)[i];
		child->draw();
		glTranslatef(child->getXPos() + child->getWidth(), 0, 0);
	}
}

// Handle onClick event, convert layout coordinates to children coordinates and call onclick on them
void HorizontalLayout::onClick(int nButton, int nState, float nX, float nY)
{
	float nCurXPos = 0;
	for (int i=0; i<m_children->size(); i++)
	{
		GuiElement *child = (*m_children)[i];
		float nChildClickX = (nX - child->getXPos() - nCurXPos) / child->getWidth();
		float nChildClickY = (nY - child->getYPos()) / child->getHeight();
		nCurXPos += child->getXPos() + child->getWidth();
		float *nPadding = child->getPadding();
		if (nChildClickX >= nPadding[0] && nChildClickX <= (1.0f - nPadding[1])
			&& nChildClickY >= nPadding[2] && nChildClickY <= (1.0f - nPadding[3]))
		{
			child->onClick(nButton, nState, nChildClickX, nChildClickY);
		}
	}
}