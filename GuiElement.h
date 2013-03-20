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
	float m_nColor[4];	// RGBA values of the background color.

	GuiElement *m_parent;				// Parent element. All nodes have one except for the root.

public:
	GuiElement(GuiElement *parent = 0);
	virtual void draw();

	void setId(string sId);
	void setWidth(float nWidth);
	void setHeight(float nHeight);
	void setXPos(float nXPos);
	void setYPos(float nYPos);
	void setColor(float nR, float nG, float nB, float nA);
	string getId();
	float getWidth();
	float getHeight();
	float getXPos();
	float getYPos();
	float *getColor();
	GuiElement *getParent();
};

#endif