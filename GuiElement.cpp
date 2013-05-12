#include "GuiElement.h"
#include "DrawFunc.h"
#include "TextureManager.h"

GuiElement::GuiElement(GuiElement *parent)
{
	m_parent = parent;
	m_sId = "";
	m_sBackgroundImage = "";
	m_nWidth = 1.0f;
	m_nHeight = 1.0f;
	m_nXPos = 0;
	m_nYPos = 0;
	for (int i=0; i<4; i++)
	{
		m_nColor[i] = 1.0f;
		m_nColorExtra[i] = 0.0f;
		m_nPadding[i] = 0.0f;
	}
}

void GuiElement::draw()
{
	glPushMatrix();
		glMatrixMode(GL_MODELVIEW);
		glTranslatef(m_nXPos, m_nYPos, 0);
		glScalef(m_nWidth, m_nHeight, 0);
		glColor4f(m_nColor[0]+m_nColorExtra[0], m_nColor[1]+m_nColorExtra[1], m_nColor[2]+m_nColorExtra[2], m_nColor[3]+m_nColorExtra[3]);
		if (m_sBackgroundImage.length() > 0)
		{
			TextureManager::getInstance()->bindTexture(m_sBackgroundImage);
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		drawScreen(m_nPadding[0], m_nPadding[2], 1.0f-m_nPadding[1], 1.0f-m_nPadding[3]);
	glPopMatrix();
}

void GuiElement::onClick(int nButton, int nState, float nX, float nY)
{
}

void GuiElement::setId(string sId)
{
	m_sId = sId;
}
	
void GuiElement::setDimensions(float nXPos, float nYPos, float nWidth, float nHeight)
{
	setWidth(nWidth);
	setHeight(nHeight);
	setXPos(nXPos);
	setYPos(nYPos);
}

void GuiElement::setWidth(float nWidth)
{
	m_nWidth = nWidth;
}
	
void GuiElement::setHeight(float nHeight)
{
	m_nHeight = nHeight;
}
	
void GuiElement::setXPos(float nXPos)
{
	m_nXPos = nXPos;
}
	
void GuiElement::setYPos(float nYPos)
{
	m_nYPos = nYPos;
}
	
void GuiElement::setColor(float nR, float nG, float nB, float nA)
{
	m_nColor[0] = nR;
	m_nColor[1] = nG;
	m_nColor[2] = nB;
	m_nColor[3] = nA;
}

void GuiElement::setColorExtra(float nR, float nG, float nB, float nA)
{
	m_nColorExtra[0] = nR;
	m_nColorExtra[1] = nG;
	m_nColorExtra[2] = nB;
	m_nColorExtra[3] = nA;
}

void GuiElement::setPadding(float nLeft, float nRight, float nBottom, float nTop)
{
	m_nPadding[0] = nLeft;
	m_nPadding[1] = nRight;
	m_nPadding[2] = nBottom;
	m_nPadding[3] = nTop;
}
	
void GuiElement::setPadding(float nAmt)
{
	setPadding(nAmt, nAmt, nAmt, nAmt);
}

void GuiElement::setBackground(string sTexture)
{
	m_sBackgroundImage = sTexture;
}
	
string GuiElement::getId()
{
	return m_sId;
}
	
float GuiElement::getWidth()
{
	return m_nWidth;
}
	
float GuiElement::getHeight()
{
	return m_nHeight;
}
	
float GuiElement::getXPos()
{
	return m_nXPos;
}
	
float GuiElement::getYPos()
{
	return m_nYPos;
}
	
float *GuiElement::getColorExtra()
{
	return m_nColorExtra;
}

float *GuiElement::getColor()
{
	return m_nColor;
}

float *GuiElement::getPadding()
{
	return m_nPadding;
}

string GuiElement::getBackground()
{
	return m_sBackgroundImage;
}
	
GuiElement *GuiElement::getParent()
{
	return m_parent;
}

void GuiElement::setParent(GuiElement *parent)
{
	m_parent = parent;
}
