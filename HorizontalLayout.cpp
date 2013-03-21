#include "HorizontalLayout.h"
#include "DrawFunc.h"

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