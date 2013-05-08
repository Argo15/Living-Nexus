#ifndef VERTICALLAYOUT_H
#define VERTICALLAYOUT_H

#include "Layout.h"

/*
 * Author: wcrane
 * Date: 3/20/2013
 *
 * Layout for placing elements along the y-axis.
 */
class VerticalLayout : public Layout
{
public:
	VerticalLayout(GuiElement *parent = 0);
	void drawChildren();
	void onClick(int nButton, int nState, float nX, float nY);
};

#endif