#include "InventoryGui.h"
#include "DrawFunc.h"
#include "UserSession.h"

InventoryGui* InventoryGui::m_pInstance = 0;

InventoryGui::InventoryGui(GuiElement *parent)
{
	m_children = 0;
}

InventoryGui *InventoryGui::getInstance(GuiElement *parent)
{
	if (m_pInstance == 0)
	{
		m_pInstance = new InventoryGui(parent);
	}
	return m_pInstance;
}

void InventoryGui::init()
{
	if (m_children != 0)
	{
		delete[] m_children;
	}
	User *user = UserSession::getInstance()->getActiveUser();
	int nInventorySize = user->getInventorySize();
	m_nNumChildren = nInventorySize;
	m_children = new GuiElement*[m_nNumChildren];

	float nRadius = 0.4f;
	float nBoxSize = 2.0f/nInventorySize;

	for (int i=0; i<nInventorySize; i++)
	{
		float nColorR = 1.0f;
		float nColorG = 1.0f;
		float nColorB = 1.0f;
		m_children[i] = new Button("", this);
		m_children[i]->setWidth(nBoxSize);
		m_children[i]->setHeight(nBoxSize);
		m_children[i]->setColor(nColorR, nColorG, nColorB, 1.0);
		float nAngle = 2.0f * 3.1415f * i / nInventorySize;
		m_children[i]->setXPos(0.5f - nBoxSize / 2.0f + nRadius * cos(nAngle));
		m_children[i]->setYPos(0.5f - nBoxSize / 2.0f + nRadius * sin(nAngle));

		Object *invItem = user->getInventoryObject(i);
		if (invItem !=0)
		{
			m_children[i]->setBackground(invItem->getInventoryTexture());
		}
	}
	m_options = new OptionsGui();
	m_options->setDimensions(0.4f,0.4f,0.3f,0.24f);
	m_useButton = new Button("Use", this, this);
	m_useButton->setTextSize(0.4f, 0.4f);
	m_useButton->centerTextPos();
	m_useButton->setPadding(0.04f,0.04f,0.08f,0.08f);
	m_cancelButton = new Button("Cancel", this, this);
	m_cancelButton->setTextSize(0.7f, 0.4f);
	m_cancelButton->centerTextPos();
	m_cancelButton->setPadding(0.04f,0.04f,0.08f,0.08f);
	m_options->addButton(m_useButton);
	m_options->addButton(m_cancelButton);
}

void InventoryGui::drawChildren()
{
	for (int i=0; i<m_nNumChildren; i++)
	{
		GuiElement *child = m_children[i];
		child->draw();
	}
}

void InventoryGui::draw()
{
	User *user = UserSession::getInstance()->getActiveUser();
	int nInventorySize = user->getInventorySize();

	glPushMatrix();
		float *nPadding = this->getPadding();
		glTranslatef(this->getXPos()+this->getWidth()*nPadding[0], this->getYPos()+this->getHeight()*nPadding[2], 0);
		glScalef(this->getWidth()*(1.0f-nPadding[0]-nPadding[1]), this->getHeight()*(1.0f-nPadding[2]-nPadding[3]), 0);
		drawChildren();
		if (m_nClickedChild >= 0 && m_nClickedChild < nInventorySize)
		{
			float nAngle = 2.0f * 3.1415f * m_nClickedChild / nInventorySize;
			float nRadius = 0.15f;
			m_options->setXPos(0.5f - m_options->getWidth() / 2.0f + nRadius * cos(nAngle));
			m_options->setYPos(0.5f - m_options->getHeight() / 2.0f + nRadius * sin(nAngle));
			m_options->draw();
		}
	glPopMatrix();
}

GuiElement *InventoryGui::getChild(int nIndex)
{
	return m_children[nIndex];
}

void InventoryGui::onClick(int nButton, int nState, float nX, float nY)
{
	for (int i=0; i<m_nNumChildren; i++)
	{
		GuiElement *child = m_children[i];
		float nChildClickX = (nX - child->getXPos()) / child->getWidth();
		float nChildClickY = (nY - child->getYPos()) / child->getHeight();
		float *nPadding = child->getPadding();
		if (nChildClickX >= nPadding[0] && nChildClickX <= (1.0f - nPadding[1])
			&& nChildClickY >= nPadding[2] && nChildClickY <= (1.0f - nPadding[3]))
		{
			child->onClick(nButton, nState, nChildClickX, nChildClickY);
			User *user = UserSession::getInstance()->getActiveUser();
			Object *obj = user->getInventoryObject(i);
			if (obj != 0)
			{
				m_options->getHeaderLabel()->setText(obj->getWorldTile());
				m_nClickedChild = i;
			}
			else
			{
				m_nClickedChild = -1;
			}
			return;
		}
	}
	if (m_nClickedChild >= 0)
	{
		float nChildClickX = (nX - m_options->getXPos()) / m_options->getWidth();
		float nChildClickY = (nY - m_options->getYPos()) / m_options->getHeight();
		float *nPadding = m_options->getPadding();
		if (nChildClickX >= nPadding[0] && nChildClickX <= (1.0f - nPadding[1])
			&& nChildClickY >= nPadding[2] && nChildClickY <= (1.0f - nPadding[3]))
		{
			m_options->onClick(nButton, nState, nChildClickX, nChildClickY);
		}
		else
		{
			m_nClickedChild = -1;
		}
	}
}

void InventoryGui::buttonClicked(Button *button)
{
	if (button == m_cancelButton)
	{
		m_nClickedChild = -1;
		this->setColorExtra(0, 0, 0, 0);
	}
}