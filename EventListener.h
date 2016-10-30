#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include <string>
using namespace std;

/*
 * Author: wcrane
 * Date: 5/13/2013
 *
 * Interface that allows you to respond to event calls through the EventManager
 */
class EventListener
{
public:
	virtual void eventTriggered(string sEventName, void *pEventData) = 0;
};

#endif