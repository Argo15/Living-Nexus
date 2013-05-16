#ifndef CLICKMANAGER_H
#define CLICKMANAGER_H

#include <vector>
#include "EventListener.h"
#include "ClickObject.h"
#include "SelectionBuffer.h"

/*
 * Author: wcrane
 * Date: 5/14/2013
 *
 * Module that will handle the click events in the 3D scene. 
 * Draws all ClickObjects to a buffer as a different color, 
 * then reads that buffer to find the selected object.
 */
class ClickManager : public EventListener
{
private:
	static ClickManager *m_pInstance;
	SelectionBuffer *m_selectionBuffer;
	vector<ClickObject *> m_clickObjects;
	View *m_view;
	Camera *m_camera;

	void handleClickEvent(void *pEventData);
	ClickManager();
public:
	static ClickManager *getInstance();

	void addClickObject(ClickObject *clickObject);
	void clear();
	void eventTriggered(string sEventName, void *pEventData);

	void setView(View *view);
	void setCamera(Camera *camera);
	SelectionBuffer *getSelectionBuffer();
};

#endif