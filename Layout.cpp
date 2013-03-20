#include "Layout.h"

Layout::Layout(GuiElement *parent) : GuiElement(parent)
{
	m_children = new vector<GuiElement *>();
}

void Layout::addElement(GuiElement *element)
{
	m_children->push_back(element);
}

vector<GuiElement *> *Layout::getChildren()
{
	return m_children;
}