#ifndef LAYOUT_H
#define LAYOUT_H

#include "GuiElement.h"

/*
 * Author: wcrane
 * Date: 3/19/2013
 *
 * Abstract Layout gui element that can be used to organize child elements.
 */
class Layout : public GuiElement
{
protected:
	vector<GuiElement *> *m_children;	// Children elements.

public:
	Layout(GuiElement *parent = 0);

	void draw();
	virtual void drawChildren() = 0;
	void addElement(GuiElement *element);
	vector<GuiElement *> *getChildren();
};

#endif