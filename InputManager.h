#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <set>
#include "EventManager.h"

class InputManager : public EventListener
{
private:
	bool m_bKeys[256];
	bool m_bKeysPressedNotChecked[256];
	bool m_bMouseButtons[5];
	std::set<int> m_hsSpecialKeyPressed;
	int m_nMouseX, m_nMouseY;
	bool m_bMouseCentered;
	bool m_bMouseMoved;

public:
	InputManager();

	void registerKeyDown(int nKey);
	void registerKeyUp(int nKey);
	bool isKeyDown(int nKey);
	bool isSpecialKeyDown(int nKey);
	bool isKeyDownOnce(int nKey);

	void registerMouseButtonDown(int nMouse);
	void registerMouseButtonUp(int nMouse);
	void setMousePosition(int nPosX, int nPosY);
	void setMouseCentered(int nPosX, int nPosY);
	bool isMouseButtonDown(int nMouse);
	int getMouseX();
	int getMouseY();
	bool isMouseMoved();

	void eventTriggered(string sEventName, void *pEventData);
};

extern InputManager *gInputManager;

#endif