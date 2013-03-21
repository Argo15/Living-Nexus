#ifndef HORIZONTALLAYOUT_H
#define HORIZONTALLAYOUT_H

#include "Layout.h"

/*
 * Author: wcrane
 * Date: 3/20/2013
 *
 * Layout for placing elements along the x-axis.
 */
class HorizontalLayout : public Layout
{
public:
	HorizontalLayout(GuiElement *parent = 0);
	void drawChildren();
};

#endif