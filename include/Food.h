#pragma once

#include <SFML/Graphics.hpp>

class Food
{
public:
	Food();

	void update(float delta);
	void draw(sf::RenderWindow& window);
	void spawnFood();
	
	sf::FloatRect getBounds();

private:
	sf::RectangleShape shape = sf::RectangleShape(sf::Vector2f(20.f, 20.f));

	float getRandomValue(int min, int max);
};