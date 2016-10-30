#ifndef OPTIONSGUI_H
#define OPTIONSGUI_H

#include "RelativeLayout.h"
#include "VerticalLayout.h"
#include "Button.h"
#include <vector>
using namespace std;

/*
 * Author: wcrane
 * Date: 5/9/2013
 *
 * Gui Object that holds a Label followed by a number of Buttons.
 */
class OptionsGui : public RelativeLayout
{
private:
	Layout *m_mainLayout;
	GuiElement *m_background;
	Label *m_hdrLabel;
	vector<Button *> m_buttons;

	void updateDimensions();

public:
	OptionsGui();
	
	Label *getHeaderLabel();
	void addButton(Button *button);
};

#endif