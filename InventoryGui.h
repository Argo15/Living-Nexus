#ifndef INVENTORYGUI_H
#define INVENTORYGUI_H

#include "GuiElement.h"
#include "View.h"

/*
 * Author: wcrane
 * Date: 4/6/2013
 *
 * Gui layer for the users inventory.
 */
class InventoryGui : public GuiElement
{
private:
	GuiElement **m_children;	// Children elements.

	void drawChildren();

public:
	InventoryGui(GuiElement *parent = 0);

	void initialize(View *view);
	void draw();
	GuiElement *getChild(int nIndex);
	void onClick(int nButton, int nState, float nX, float nY);
};

#endif