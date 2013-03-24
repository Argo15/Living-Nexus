#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include "GuiElement.h"

/*
 * Author: wcrane
 * Date: 3/19/2013
 *
 * Manages the main GUI layer. Consists of a single root node.
 */
class GuiManager 
{
private:
	static GuiManager *m_pInstance;
	GuiElement *m_rootElement;

	GuiManager();

public:
	static GuiManager *getInstance();
	void render();

	// event handlers
	void onClick(int nButton, int nState, float nX, float nY);

	void setRootElement(GuiElement *element);
	GuiElement *getRootElement();
};

#endif