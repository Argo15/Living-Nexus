#include "OptionsGui.h"

OptionsGui::OptionsGui() : RelativeLayout()
{
	m_mainLayout = new VerticalLayout();

	m_background = new GuiElement();
	m_background->setColor(0.8f, 0.8f, 0.8f, 1.0f);

	m_hdrLabel = new Label("Options", this);
	m_hdrLabel->setTextSize(0.8f, 0.8f);
	m_hdrLabel->centerTextPos();
	m_hdrLabel->setPadding(0.04f,0.04f,0.08f,0.08f);

	m_mainLayout->addElement(m_hdrLabel);
	for (int i=0; i<m_buttons.size(); i++)
	{
		m_mainLayout->addElement(m_buttons[i]);
	}

	this->addElement(m_background);
	this->addElement(m_mainLayout);

	updateDimensions();
}

void OptionsGui::updateDimensions()
{
	for (int i=0; i<m_buttons.size(); i++)
	{
		m_buttons[i]->setHeight(1.0f/((float)m_buttons.size()+1.0f));
	}
	m_hdrLabel->setHeight(1.0f/((float)m_buttons.size()+1.0f));
}

Label *OptionsGui::getHeaderLabel()
{
	return m_hdrLabel;
}

void OptionsGui::addButton(Button *button)
{
	m_buttons.push_back(button);
	m_mainLayout->addElement(button);
	updateDimensions();
}