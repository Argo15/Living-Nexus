#include "Button.h"
#include "DrawFunc.h"

Button::Button(string sText, ButtonListener *listener, GuiElement *parent) : Label(sText, parent)
{
	m_listener = listener;
}

void Button::onClick(int nButton, int nState, float nX, float nY)
{
	if (nState == GLUT_DOWN)
	{
		this->setColorExtra(-0.2f, -0.2f, -0.2f, 0);
	}
	else
	{
		this->setColorExtra(0, 0, 0, 0);
		if (m_listener != 0)
		{
			m_listener->buttonClicked(this);
		}
	}
}