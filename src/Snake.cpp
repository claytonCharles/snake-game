#include "Snake.h"
#include <typeinfo>
#include <algorithm>

Snake::Snake() 
{
	sf::RectangleShape segment(sf::Vector2f(snakeBodyBox, snakeBodyBox));
	segment.setFillColor(sf::Color::Green);

	for (int i = 0; i <= 3; i++)
	{
		sf::Vector2f tt = sf::Vector2f(700 + i * snakeBodyBox, 0);
		segment.setPosition(tt);
		body.push_back(segment);
	}

	direction = { -1, 0 };
}

void Snake::draw(sf::RenderWindow& window)
{
	for (auto& segment : body)
	{
		window.draw(segment);
	}
}

void Snake::update(float delta)
{
	timer += delta;
	if (timer >= delay)
	{
		timer = 0.f;
		move(delta);
	}
}

void Snake::move(float delta)
{
	sf::Vector2f currentPosition = body[0].getPosition();
	Snake::moveSnakeHead(currentPosition, delta);

	for (int i = 1; i <= body.size() - 1; i++)
	{	
		sf::Vector2f targetPosition = currentPosition;
		currentPosition = body[i].getPosition();
		body[i].setPosition(targetPosition);
	}
}

void Snake::setScreenSpace(sf::Vector2f screen)
{
	screenSpace = screen;
}

void Snake::updateDirection(sf::Vector2i targetDirection)
{
	if (direction.x != 0 && targetDirection.x != 0) return;
	if (direction.y != 0 && targetDirection.y != 0) return;
	direction = targetDirection;
}

void Snake::moveSnakeHead(sf::Vector2f currentPosition, float delta)
{
	currentPosition.x += direction.x * snakeBodyBox;
	currentPosition.y += direction.y * snakeBodyBox;

	if (currentPosition.x <= -snakeBodyBox)
	{
		currentPosition.x = screenSpace.x;
	}

	if (currentPosition.x >= screenSpace.x + snakeBodyBox)
	{
		currentPosition.x = 0;
	}

	if (currentPosition.y <= -snakeBodyBox)
	{
		currentPosition.y = screenSpace.y;
	}

	if (currentPosition.y >= screenSpace.y + snakeBodyBox)
	{
		currentPosition.y = 0;
	}

	body[0].setFillColor(sf::Color::Blue);
	body[0].setPosition(currentPosition);
}