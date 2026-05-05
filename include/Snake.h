#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Snake {
public:
	Snake();

	void draw(sf::RenderWindow& window);
	void update(float delta);
	void move(float delta);
	void updateDirection(sf::Vector2i direction);
	void setScreenSpace(sf::Vector2f screen);
	void grow();

	sf::FloatRect getHeadBounds();
	std::vector<sf::FloatRect> getBodyBounds();

private:
	sf::RectangleShape head = sf::RectangleShape(sf::Vector2f(20.f, 20.f));
	std::vector<sf::RectangleShape> body;

	sf::Vector2f screenSpace;

	float timer = 0.f;
	float delay = 0.1f;
	float snakeBodyBox = 20.f;

	sf::Vector2i direction;

	void moveSnakeHead(sf::Vector2f currentPosition, float delta);
};