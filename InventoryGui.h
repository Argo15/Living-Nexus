#ifndef INVENTORYGUI_H
#define INVENTORYGUI_H

#include "SquareFrame.h"
#include "View.h"
#include "ButtonListener.h"
#include "OptionsGui.h"

/*
 * Author: wcrane
 * Date: 4/6/2013
 *
 * Gui layer for the users inventory.
 */
class InventoryGui : public GuiElement, public ButtonListener
{
private:
	static InventoryGui *m_pInstance;
	int m_nNumChildren;
	GuiElement **m_children;	// Children elements.
	int m_nClickedChild;

	OptionsGui *m_options;
	Button *m_useButton;
	Button *m_cancelButton;

	void drawChildren();

	InventoryGui(GuiElement *parent = 0);

public:
	static InventoryGui *getInstance(GuiElement *parent = 0);

	void init();
	void draw();
	GuiElement *getChild(int nIndex);
	void onClick(int nButton, int nState, float nX, float nY);
	void buttonClicked(Button *button);
};

#endif