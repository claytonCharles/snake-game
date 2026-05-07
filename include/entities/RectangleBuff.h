#pragma once

#include <SFML/Graphics.hpp>
#include "Buffs.h"

class RectangleBuff
{
public:
	RectangleBuff();

	sf::Color rectColor;
	EBuffs randomBuff;

	RectangleBuff GetRandomBuff();

private:
	int getRandomNum(int min, int max);
};