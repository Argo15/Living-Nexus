#include "EventManager.h"

EventManager* EventManager::m_pInstance = 0;

EventManager *EventManager::getInstance() 
{
	if (m_pInstance == 0) 
	{
		m_pInstance = new EventManager();
	}
	return m_pInstance;
}

EventManager::EventManager()
{
}

void EventManager::addListener(string sEventName, EventListener *eventListener)
{
	m_eventListeners[sEventName].insert(eventListener);
}
	
void EventManager::notify(string sEventName, void *pEventData)
{
	for(set<EventListener *>::iterator it = m_eventListeners[sEventName].begin(); it != m_eventListeners[sEventName].end(); it++)
	{
		(*it)->eventTriggered(sEventName, pEventData);
	}
}
	
void EventManager::removeObserver(string sEventName, EventListener *eventListener)
{
	m_eventListeners[sEventName].erase(eventListener);
}