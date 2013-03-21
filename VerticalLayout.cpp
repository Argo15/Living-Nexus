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