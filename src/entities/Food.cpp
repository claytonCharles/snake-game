#include "entities/Food.h";
#include <iostream>
#include <random>


Food::Food() {};

void Food::Ready(sf::Vector2f initJail, sf::Vector2f endJail)
{
	m_initJail = initJail;
	m_endJail = endJail;
	SpawnFood(std::nullopt);
}

void Food::SpawnFood(std::optional<RectangleBuff> buff)
{
	m_buff = std::nullopt;
	if (buff)
	{
		m_shape.setFillColor(buff->rectColor);
		m_buff = buff.value();
	}
	else
	{
		m_shape.setFillColor(sf::Color::Green);
	}

	sf::Vector2f spawnPosition = getRandomValue(m_initJail, m_endJail, 20.f);
	m_shape.setPosition(spawnPosition);
}

void Food::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_shape);
}

sf::FloatRect Food::GetBounds()
{
	return m_shape.getGlobalBounds();
}

sf::Vector2f Food::getRandomValue(sf::Vector2f min, sf::Vector2f max, float gridShape)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	int minSpawnX = min.x / gridShape;
	int minSpawnY = min.y / gridShape;
	int maxSpawnX = max.x / gridShape;
	int maxSpawnY = max.y / gridShape;

	std::uniform_int_distribution<> distribX(minSpawnX, maxSpawnX);
	std::uniform_int_distribution<> distribY(minSpawnY, maxSpawnY);

	int spanwX = distribX(gen);
	int spawnY = distribY(gen);

	return sf::Vector2f(spanwX * gridShape, spawnY * gridShape);
}