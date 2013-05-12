#include "Label.h"
#include "FreeTypeManager.h"

Label::Label(string sText, GuiElement *parent)
	: GuiElement(parent)
{
	m_sText = sText;
	m_nTextColor[0] = 0;
	m_nTextColor[1] = 0;
	m_nTextColor[2] = 0;
	m_nTextColor[3] = 1.0f;
	m_nTextPosition[0] = 0;
	m_nTextPosition[1] = 0;
	m_nTextSize[0] = 1.0f;
	m_nTextSize[1] = 1.0f;
}

void Label::draw()
{
	GuiElement::draw();
	glPushMatrix();
		float nTextScaleX = 1.0f/FreeTypeManager::getInstance()->getFont()->getPhraseWidth(m_sText, m_nTextPosition[0], m_nTextSize[1]);
		float nPaddedTextScaleX = m_nTextSize[0]*this->getWidth()*nTextScaleX * (1.0f - this->getPadding()[0] - this->getPadding()[2]);
		float nPaddedTextScaleY = this->getHeight()*(1.0f - this->getPadding()[1] - this->getPadding()[3]);
		glTranslatef(this->getXPos() + this->getPadding()[0], this->getYPos() + this->getPadding()[1]/2.0f, 0);
		glScalef(nPaddedTextScaleX, nPaddedTextScaleY, 0);
		glColor4f(m_nTextColor[0], m_nTextColor[1], m_nTextColor[2], m_nTextColor[3]);
		FreeTypeManager::getInstance()->getFont()->draw(m_sText, m_nTextPosition[0]/nPaddedTextScaleX, m_nTextPosition[1], m_nTextSize[1]);
	glPopMatrix();
}

void Label::setText(string text)
{
	m_sText = text;
}

void Label::setTextColor(float nR, float nG, float nB, float nA)
{
	m_nTextColor[0] = nR;
	m_nTextColor[1] = nG;
	m_nTextColor[2] = nB;
	m_nTextColor[3] = nA;
}

void Label::setTextSize(float nSizeX, float nSizeY)
{
	m_nTextSize[0] = nSizeX;
	m_nTextSize[1] = nSizeY;
}

void Label::setTextPos(float nX, float nY)
{
	m_nTextPosition[0] = nX;
	m_nTextPosition[1] = nY;
}

void Label::centerTextPos()
{
	m_nTextPosition[0] = (1.0f-m_nTextSize[0])/2.0f;
	m_nTextPosition[1] = (1.0f-m_nTextSize[1])/2.0f;
}