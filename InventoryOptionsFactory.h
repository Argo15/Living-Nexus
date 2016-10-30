#ifndef INVENTORYOPTIONSFACTORY_H
#define INVENTORYOPTIONSFACTORY_H

#include "OptionsGui.h"
#include <map>
using namespace std;

enum OptionsType
{
	USE_OPTIONS,
	SHOP_OPTIONS
};

class InventoryGui;

/*
 * Author: wcrane
 * Date: 6/2/2013
 *
 * Factory class that will create the different types of 
 * OptionsGui that the inventory gui will use.
 */
class InventoryOptionsFactory
{
private:
	static map<OptionsType, OptionsGui *> m_options;

public:
	static OptionsGui *getOptionsGui(OptionsType optionsType, InventoryGui *buttonListener);
};

#endif