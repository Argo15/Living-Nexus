#ifndef GUIELEMENT_H
#define GUIELEMENT_H

#include <string>
#include <vector>
using namespace std;

/*
 * Author: wcrane
 * Date: 3/19/2013
 *
 * Abstract GUI Element node object
 */
class GuiElement
{
private:
	string m_sId;		// A unique id for the element so that you can query it later.
	float m_nWidth;		// A number from 0 - 1.0 representing a percentage of the parent element width to fill.
	float m_nHeight;	// A number from 0 - 1.0 representing a percentage of the parent element height to fill.
	float m_nXPos;		// X value between 0 - 1.0 for the bottom left of the element
	float m_nYPos;		// Y value between 0 - 1.0 for the bottom left of the element
	float m_nPadding[4];// left, right, bottom, top padding
	float m_nColor[4];	// RGBA values of the background color.
	float m_nColorExtra[4];	// Additional color values that can be used for clicking, hovers, ect.
	string m_sBackgroundImage; // Name of texture for background.

	GuiElement *m_parent;				// Parent element. All nodes have one except for the root.

public:
	GuiElement(GuiElement *parent = 0);
	virtual void draw();

	// events
	virtual void onClick(int nButton, int nState, float nX, float nY);

	void setId(string sId);
	void setDimensions(float nXPos, float nYPos, float nWidth, float nHeight);
	void setWidth(float nWidth);
	void setHeight(float nHeight);
	void setXPos(float nXPos);
	void setYPos(float nYPos);
	void setColor(float nR, float nG, float nB, float nA);
	void setColorExtra(float nR, float nG, float nB, float nA);
	void setPadding(float nLeft, float nRight, float nBottom, float nTop);
	void setPadding(float nAmt);
	void setBackground(string sTexture);
	string getId();
	float getWidth();
	float getHeight();
	float getXPos();
	float getYPos();
	float *getColor();
	float *getColorExtra();
	float *getPadding();
	string getBackground();
	GuiElement *getParent();
	void setParent(GuiElement *parent);
};

#endif