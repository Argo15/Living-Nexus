#ifndef BUTTON_H
#define BUTTON_H

#include "Label.h"
#include "ButtonListener.h"

/*
 * Author: wcrane
 * Date: 5/9/2013
 *
 * Base Gui element for rendering a button.
 */
class Button : public Label
{
private:
	ButtonListener *m_listener;

public:
	Button(string sText, ButtonListener *listener = 0, GuiElement *parent = 0);

	virtual void onClick(int nButton, int nState, float nX, float nY);
};

#endif