#include "InventoryOptionsFactory.h"
#include "InventoryGui.h"

map<OptionsType, OptionsGui *> InventoryOptionsFactory::m_options;

OptionsGui *InventoryOptionsFactory::getOptionsGui(OptionsType optionsType, InventoryGui *inventory)
{
	if (optionsType == USE_OPTIONS)
	{
		// Standard type of options when you have an option to use an object
		if (m_options.find(USE_OPTIONS) == m_options.end())
		{
			OptionsGui *options = new OptionsGui();
			options->setDimensions(0.4f,0.4f,0.3f,0.24f);
			Button *useButton = new Button("Use", inventory, inventory);
			useButton->setTextSize(0.4f, 0.4f);
			useButton->centerTextPos();
			useButton->setPadding(0.04f,0.04f,0.08f,0.08f);
			Button *cancelButton = new Button("Cancel", inventory, inventory);
			cancelButton->setTextSize(0.7f, 0.4f);
			cancelButton->centerTextPos();
			cancelButton->setPadding(0.04f,0.04f,0.08f,0.08f);
			options->addButton(useButton);
			options->addButton(cancelButton);
			m_options[USE_OPTIONS] = options;
		}
		return m_options[USE_OPTIONS];
	}
	else if (optionsType == SHOP_OPTIONS)
	{
		// Options for when you are selling objects
		if (m_options.find(SHOP_OPTIONS) == m_options.end())
		{
			OptionsGui *options = new OptionsGui();
			options->setDimensions(0.4f,0.4f,0.3f,0.24f);
			Button *sellButton = new Button("Sell", inventory, inventory);
			sellButton->setTextSize(0.4f, 0.4f);
			sellButton->centerTextPos();
			sellButton->setPadding(0.04f,0.04f,0.08f,0.08f);
			Button *cancelButton = new Button("Cancel", inventory, inventory);
			cancelButton->setTextSize(0.7f, 0.4f);
			cancelButton->centerTextPos();
			cancelButton->setPadding(0.04f,0.04f,0.08f,0.08f);
			options->addButton(sellButton);
			options->addButton(cancelButton);
			m_options[SHOP_OPTIONS] = options;
		}
		return m_options[SHOP_OPTIONS];
	}
	else
	{
		return 0;
	}
}