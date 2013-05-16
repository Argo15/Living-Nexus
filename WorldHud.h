#ifndef WORLDHUD_H
#define WORLDHUD_H

#include "SquareFrame.h"

/*
 * Author: wcrane
 * Date: 5/13/2013
 *
 * Gui Object for the heads up display while browsing the world
 */
class WorldHud : public SquareFrame
{
private:
	GuiElement *m_reticle;

public:
	WorldHud(GuiElement *parent = 0);
};

#endif