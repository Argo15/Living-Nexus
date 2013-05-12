#ifndef OPTIONSGUI_H
#define OPTIONSGUI_H

#include "RelativeLayout.h"
#include "VerticalLayout.h"
#include "Button.h"
#include <vector>
using namespace std;

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