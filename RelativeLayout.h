#ifndef RELATIVELAYOUT_H
#define RELATIVELAYOUT_H

#include "Layout.h"

/*
 * Author: wcrane
 * Date: 3/19/2013
 *
 * Layout gui element that allows you to place child elements in any location.
 */
class RelativeLayout : public Layout
{
	public:
	RelativeLayout(GuiElement *parent = 0);

	void drawChildren();
	void onClick(int nButton, int nState, float nX, float nY);
};

#endif