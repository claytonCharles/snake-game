#include "Food.h";
#include <iostream>
#include <random>


Food::Food()
{
	spawnFood();
}

void Food::update(float delta)
{
}

void Food::spawnFood()
{
	int spawnX = getRandomValue(0, 40);
	int spawnY = getRandomValue(0, 30);

	sf::Vector2f spawnPosition = sf::Vector2f(spawnX * 20.f, spawnY * 20.f);
	shape.setFillColor(sf::Color::Red);
	shape.setPosition(spawnPosition);
}

void Food::draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

sf::FloatRect Food::getBounds()
{
	return shape.getGlobalBounds();
}

float Food::getRandomValue(int min, int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(min, max);
	return (float)distrib(gen);
}