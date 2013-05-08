#include "GuiManager.h"
#include "MaterialManager.h"
#include "Logger.h"
#include "DrawFunc.h"

GuiManager* GuiManager::m_pInstance = 0;

GuiManager::GuiManager()
{
	m_rootElement = 0;
}

GuiManager *GuiManager::getInstance()
{
	if (m_pInstance == 0)
	{
		m_pInstance = new GuiManager();
	}
	return m_pInstance;
}

void GuiManager::render()
{
	if (m_rootElement != 0)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		MaterialManager::getInstance()->useMaterial("Default");
		m_rootElement->draw();
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glBlendFunc(GL_ONE, GL_ZERO);
	}
}

void GuiManager::onClick(int nButton, int nState, float nX, float nY)
{
	if (m_rootElement != 0)
	{
		m_rootElement->onClick(nButton, nState, nX, nY);
	}
}

void GuiManager::setRootElement(GuiElement *element)
{
	m_rootElement = element;
}

GuiElement *GuiManager::getRootElement()
{
	return m_rootElement;
}
