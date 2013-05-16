#include "WorldHud.h"

WorldHud::WorldHud(GuiElement *parent) : SquareFrame(parent)
{
	m_reticle = new GuiElement(this);
	m_reticle->setColor(1.0f, 1.0f, 1.0f, 0.8f);
	m_reticle->setDimensions(0.49f, 0.49f, 0.02f, 0.02f);
	this->addElement(m_reticle);
}