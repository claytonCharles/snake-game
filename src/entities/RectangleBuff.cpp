#include "entities/RectangleBuff.h"
#include "entities/Buffs.h"
#include <vector>
#include <map>
#include <iostream>
#include <random>

RectangleBuff::RectangleBuff() {}

RectangleBuff RectangleBuff::GetRandomBuff()
{
	std::map<EBuffs, sf::Color> buffColors = {
		{EBuffs::Default, sf::Color::Green},
		{EBuffs::Speed, sf::Color::Cyan},
		{EBuffs::UpSize, sf::Color::Magenta},
		{EBuffs::DownSize, sf::Color::Red}
	};

	std::vector<EBuffs> buffs;
	buffs.reserve(10);

	int speedBuffs = getRandomNum(0, 4);
	int upSizeBuffs = getRandomNum(0, 4);
	int downSize = getRandomNum(0, 2);
	int defaulBuffs = 10 - (speedBuffs + upSizeBuffs - downSize);

	buffs.insert(buffs.end(), defaulBuffs, EBuffs::Default);
	buffs.insert(buffs.end(), speedBuffs, EBuffs::Speed);
	buffs.insert(buffs.end(), upSizeBuffs, EBuffs::UpSize);
	buffs.insert(buffs.end(), downSize, EBuffs::DownSize);
	std::shuffle(buffs.begin(), buffs.end(), std::mt19937(std::random_device{}()));

	int indexBuff = getRandomNum(0, buffs.size() - 1);
	EBuffs buffSorted = buffs[indexBuff];
	sf::Color buffColor = buffColors[buffSorted];

	RectangleBuff buffSelected;
	buffSelected.randomBuff = buffSorted;
	buffSelected.rectColor = buffColor;

	return buffSelected;
}

int RectangleBuff::getRandomNum(int min, int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(min, max);
	return distrib(gen);
}