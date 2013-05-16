#ifndef FRUITFACTORY_H
#define FRUITFACTORY_H

#include "Fruit.h"

static std::string S_APPLE_TILE		= "Apple";
static std::string S_APPLE_TEXTURE	= "apple-icon";
static std::string S_ORANGE_TILE	= "Orange";
static std::string S_ORANGE_TEXTURE	= "orange-icon";
static std::string S_PEAR_TILE		= "Pear";
static std::string S_PEAR_TEXTURE	= "pear-icon";
static std::string S_CHERRY_TILE	= "Cherry";
static std::string S_CHERRY_TEXTURE	= "cherry-icon";

enum FruitType 
{
	NONE, 
	APPLE, 
	ORANGE, 
	PEAR, 
	CHERRY
};

class FruitFactory 
{
public:
	static Fruit *buildFruit(FruitType type) 
	{
		switch (type) 
		{
			case NONE: 
				return 0;
			case APPLE: 
				return new Fruit("Apple", S_APPLE_TILE, S_APPLE_TEXTURE, S_APPLE_TILE);
			case ORANGE: 
				return new Fruit("Orange", S_ORANGE_TILE, S_ORANGE_TEXTURE, S_ORANGE_TILE);
			case PEAR: 
				return new Fruit("Pear", S_PEAR_TILE, S_PEAR_TEXTURE, S_PEAR_TILE);
			case CHERRY: 
				return new Fruit("Cherry", S_CHERRY_TILE, S_CHERRY_TEXTURE, S_CHERRY_TILE);
			default:
				return 0;
		}
	}
};

#endif