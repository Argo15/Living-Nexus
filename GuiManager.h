#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include "GuiElement.h"
#include "EventManager.h"

/*
 * Author: wcrane
 * Date: 3/19/2013
 *
 * Manages the main GUI layer. Consists of a single root node.
 */
class GuiManager : public EventListener
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
	
	void eventTriggered(string sEventName, void *pEventData);
};

#endif