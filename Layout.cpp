#include "Layout.h"
#include "DrawFunc.h"

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


void Layout::draw()
{
	glPushMatrix();
		float *nPadding = this->getPadding();
		glTranslatef(this->getXPos()+this->getWidth()*nPadding[0], this->getYPos()+this->getHeight()*nPadding[2], 0);
		glScalef(this->getWidth()*(1.0-nPadding[0]-nPadding[1]), this->getHeight()*(1.0-nPadding[2]-nPadding[3]), 0);
		drawChildren();
	glPopMatrix();
}