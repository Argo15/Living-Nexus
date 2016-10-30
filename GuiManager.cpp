#include "GuiManager.h"
#include "MaterialManager.h"
#include "Logger.h"
#include "DrawFunc.h"

GuiManager localGuiManager;
GuiManager *gGuiManager = &localGuiManager;

GuiManager::GuiManager()
{
	m_rootElement = 0;
	gEventManager->addListener("onMouseClick", this);
}

void GuiManager::render()
{
	if (m_rootElement != 0)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		gMaterialManager->useMaterial("Default");
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

void GuiManager::eventTriggered(string sEventName, void *pEventData)
{
	if (sEventName == "onMouseClick")
	{
		typedef struct { int nButton; int nState; float nX; float nY; } OnclickData;
		OnclickData *data = (OnclickData *)pEventData;
		this->onClick(data->nButton, data->nState, data->nX, data->nY);
	}
}