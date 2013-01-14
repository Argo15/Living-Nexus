#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <set>

class InputManager 
{
private:
	static InputManager *m_pInstance;
	bool keys[256];
	bool keysPressedNotChecked[256];
	bool mouseButtons[5];
	std::set<int> specialKeyPressed;
	int mouseX, mouseY;
	bool mouseCentered;
	bool mouseMoved;

	InputManager();
public:
	static InputManager *getInstance();

	void registerKeyDown(int key);
	void registerKeyUp(int key);
	bool isKeyDown(int key);
	bool isSpecialKeyDown(int key);
	bool isKeyDownOnce(int key);

	void registerMouseButtonDown(int mouse);
	void registerMouseButtonUp(int mouse);
	void setMousePosition(int x, int y);
	void setMouseCentered(int x, int y);
	bool isMouseButtonDown(int mouse);
	int getMouseX();
	int getMouseY();
	bool isMouseMoved();
};

#endif