#include "Snake.h"
#include <typeinfo>
#include <algorithm>

Snake::Snake() 
{
	head.setFillColor(sf::Color::Blue);
	head.setPosition(sf::Vector2f(700, 0));
	direction = { -1, 0 };
}

void Snake::draw(sf::RenderWindow& window)
{
	window.draw(head);

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
	sf::Vector2f currentPosition = head.getPosition();
	Snake::moveSnakeHead(currentPosition, delta);

	if (body.size() > 0)
	{
		for (int i = 0; i <= body.size() - 1; i++)
		{
			sf::Vector2f targetPosition = currentPosition;
			currentPosition = body[i].getPosition();
			body[i].setPosition(targetPosition);
		}
	}
}

void Snake::grow()
{
	sf::Vector2f lastPosition;
	if (body.size() >= 1)
	{
		int lastPart = body.size() - 1;
		lastPosition = body[lastPart].getPosition();
	}
	else
	{
		lastPosition = head.getPosition();
	}

	sf::RectangleShape segment(head.getSize());
	segment.setFillColor(sf::Color::Green);
	segment.setPosition(lastPosition);
	body.push_back(segment);
}

sf::FloatRect Snake::getHeadBounds()
{
	return head.getGlobalBounds();
}

std::vector<sf::FloatRect> Snake::getBodyBounds()
{
	std::vector<sf::FloatRect> bounds;
	for (auto& segment : body)
	{
		bounds.push_back(segment.getGlobalBounds());
	}

	return bounds;
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

	head.setPosition(currentPosition);
}