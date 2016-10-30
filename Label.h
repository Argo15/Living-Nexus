#ifndef LABEL_H
#define LABEL_H

#include <string>
#include "GuiElement.h"
using namespace std;

/*
 * Author: wcrane
 * Date: 5/9/2013
 *
 * Gui element for rendering text.
 */
class Label : public GuiElement
{
private:
	string m_sText;
	float m_nTextColor[4];
	float m_nTextSize[2];
	float m_nTextPosition[2];

public:
	Label(string sText, GuiElement *parent = 0);

	void draw();
	void setText(string text);
	void setTextColor(float nR, float nG, float nB, float nA);
	void setTextSize(float nSizeX, float nSizeY);
	void setTextPos(float nX, float nY);
	void centerTextPos();
	string getText();
};

#endif