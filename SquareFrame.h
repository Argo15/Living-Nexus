#ifndef SQUAREFRAME_H
#define SQUAREFRAME_H

#include "RelativeLayout.h"
#include "View.h"

/*
 * Author: wcrane
 * Date: 5/9/2013
 *
 * Gui layer that will always have dx and dy be the same distance on the screen.
 */
class SquareFrame : public RelativeLayout
{
private:
	float nHeight, nWidth;

public:
	SquareFrame(GuiElement *parent = 0);

	void drawChildren();
	void onClick(int nButton, int nState, float nX, float nY);
	
	void initialize(View *view);
};

#endif