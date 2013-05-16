#include "ClickManager.h"
#include "EventManager.h"
#include "Logger.h"
#include "StringUtils.h"

ClickManager* ClickManager::m_pInstance = 0;

ClickManager *ClickManager::getInstance() 
{
	if (m_pInstance == 0) 
	{
		m_pInstance = new ClickManager();
	}
	return m_pInstance;
}

ClickManager::ClickManager()
{
	EventManager::getInstance()->addListener("onMouseClick", this);
	m_selectionBuffer = new SelectionBuffer(1280,720);
	m_view = 0;
	m_camera = 0;
}

void ClickManager::handleClickEvent(void *pEventData)
{
	typedef struct { int nButton; int nState; float nX; float nY; } OnclickData;
	OnclickData *data = (OnclickData *)pEventData;
	if (data->nState == 0)
	{
		m_selectionBuffer->drawToBuffer(&m_clickObjects, m_view, m_camera);
		int nSelectedObj = m_selectionBuffer->getSelectedObject();
		if (nSelectedObj >= 0)
		{
			m_clickObjects[nSelectedObj]->onClick();
		}
	}
}

void ClickManager::addClickObject(ClickObject *clickObject)
{
	m_clickObjects.push_back(clickObject);
}
	
void ClickManager::clear()
{
	for (std::vector<ClickObject *>::iterator it = m_clickObjects.begin(); it != m_clickObjects.end(); it++)
	{
		ClickObject *object = (*it);
		delete object;
	}
	m_clickObjects.clear();
}

void ClickManager::eventTriggered(string sEventName, void *pEventData)
{
	if (sEventName == "onMouseClick")
	{
		this->handleClickEvent(pEventData);
	}
}

void ClickManager::setView(View *view)
{
	m_view = view;
}

void ClickManager::setCamera(Camera *camera)
{
	m_camera = camera;
}


SelectionBuffer *ClickManager::getSelectionBuffer()
{
	return m_selectionBuffer;
}