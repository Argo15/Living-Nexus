#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <map>
#include <set>
#include <string>
#include "EventListener.h"
using namespace std;

/*
 * Author: wcrane
 * Date: 5/13/2013
 *
 * Anti-pattern, probably a bad idea
 * Allows you to listen for an event name or allows you to broadcast an event.
 */
class EventManager
{
private:
	map<string, set<EventListener *> > m_eventListeners;

public:
	EventManager();

	void addListener(string sEventName, EventListener *eventListener);
	void notify(string sEventName, void *pEventData);
	void removeObserver(string sEventName, EventListener *eventListener);
};

extern EventManager *gEventManager;

#endif