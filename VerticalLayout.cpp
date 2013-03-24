#include "VerticalLayout.h"
#include "DrawFunc.h"

VerticalLayout::VerticalLayout(GuiElement *parent) : Layout(parent)
{

}

void VerticalLayout::drawChildren()
{
	for (int i=0; i<m_children->size(); i++)
	{
		GuiElement *child = (*m_children)[i];
		child->draw();
		glTranslatef(0, child->getYPos() + child->getHeight(), 0);
	}
}

// Handle onClick event, convert layout coordinates to children coordinates and call onclick on them
void VerticalLayout::onClick(int nButton, int nState, float nX, float nY)
{
	float nCurYPos = 0;
	for (int i=0; i<m_children->size(); i++)
	{
		GuiElement *child = (*m_children)[i];
		float nChildClickX = (nX - child->getXPos()) / child->getWidth();
		float nChildClickY = (nY - child->getYPos() - nCurYPos) / child->getHeight();
		nCurYPos += child->getYPos() + child->getHeight();
		float *nPadding = child->getPadding();
		if (nChildClickX >= nPadding[0] && nChildClickX <= (1.0f - nPadding[1])
			&& nChildClickY >= nPadding[2] && nChildClickY <= (1.0f - nPadding[3]))
		{
			child->onClick(nButton, nState, nChildClickX, nChildClickY);
		}
	}
}