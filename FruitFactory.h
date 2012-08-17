#ifndef FRUITFACTORY_H
#define FRUITFACTORY_H

#include "Apple.h"
#include "Orange.h"
#include "Pear.h"
#include "Cherry.h"

enum FruitType {NONE, APPLE, ORANGE, PEAR, CHERRY};

class FruitFactory {
public:
	static Fruit *buildFruit(FruitType type) {
		switch (type) {
			case NONE: return 0;
			case APPLE: return new Apple();
			case ORANGE: return new Orange();
			case PEAR: return new Pear();
			case CHERRY: return new Cherry();
		}
	}
};

#endif