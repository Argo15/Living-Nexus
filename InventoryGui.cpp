#include "InventoryGui.h"
#include "DrawFunc.h"
#include "UserSession.h"

InventoryGui::InventoryGui(GuiElement *parent)
{
	m_children = 0;
}

void InventoryGui::initialize(View *view)
{
	if (m_children != 0)
	{
		delete[] m_children;
	}
	User *user = UserSession::getInstance()->getActiveUser();
	int nInventorySize = user->getInventorySize();
	m_children = new GuiElement*[nInventorySize];

	float nRadius = 0.4f;
	float nBoxDist = sqrt(
		pow((nRadius * cos(0.0)) -
		(nRadius * cos(2.0f * 3.1415f / nInventorySize)), 2.0) +
		pow((nRadius * sin(0.0)) -
		nRadius * sin(2.0f * 3.1415f / nInventorySize), 2.0));
	float nBoxWidth = nBoxDist / 2.5f;
	float nBoxHeight = nBoxWidth * view->getAspect();

	for (int i=0; i<nInventorySize; i++)
	{
		float nColorR = 1.0f;
		float nColorG = 1.0f;
		float nColorB = 1.0f;
		m_children[i] = new GuiElement(this);
		m_children[i]->setWidth(nBoxWidth);
		m_children[i]->setHeight(nBoxHeight);
		m_children[i]->setColor(nColorR, nColorG, nColorB, 1.0);
		float nAngle = 2.0f * 3.1415f * i / nInventorySize;
		m_children[i]->setXPos(0.5f - nBoxWidth / 2.0f + nRadius * cos(nAngle) / view->getAspect());
		m_children[i]->setYPos(0.5f - nBoxHeight / 2.0f + nRadius * sin(nAngle));

		Object *invItem = user->getInventoryObject(i);
		if (invItem !=0)
		{
			m_children[i]->setBackground(invItem->getInventoryTexture());
		}
	}
}

void InventoryGui::drawChildren()
{
	int nInventorySize = UserSession::getInstance()->getActiveUser()->getInventorySize();
	for (int i=0; i<nInventorySize; i++)
	{
		GuiElement *child = m_children[i];
		child->draw();
	}
}

void InventoryGui::draw()
{
	glPushMatrix();
		float *nPadding = this->getPadding();
		glTranslatef(this->getXPos()+this->getWidth()*nPadding[0], this->getYPos()+this->getHeight()*nPadding[2], 0);
		glScalef(this->getWidth()*(1.0f-nPadding[0]-nPadding[1]), this->getHeight()*(1.0f-nPadding[2]-nPadding[3]), 0);
		drawChildren();
	glPopMatrix();
}

GuiElement *InventoryGui::getChild(int nIndex)
{
	return m_children[nIndex];
}

void InventoryGui::onClick(int nButton, int nState, float nX, float nY)
{
	int nInventorySize = UserSession::getInstance()->getActiveUser()->getInventorySize();
	for (int i=0; i<nInventorySize; i++)
	{
		GuiElement *child = m_children[i];
		float nChildClickX = (nX - child->getXPos()) / child->getWidth();
		float nChildClickY = (nY - child->getYPos()) / child->getHeight();
		float *nPadding = child->getPadding();
		if (nChildClickX >= nPadding[0] && nChildClickX <= (1.0f - nPadding[1])
			&& nChildClickY >= nPadding[2] && nChildClickY <= (1.0f - nPadding[3]))
		{
			child->onClick(nButton, nState, nChildClickX, nChildClickY);
		}
	}
}