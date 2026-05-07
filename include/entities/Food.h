#pragma once

#include <SFML/Graphics.hpp>
#include "RectangleBuff.h"
#include <optional>

class Food : public sf::Drawable
{
public:
	Food();

	void Ready(sf::Vector2f initJail, sf::Vector2f endJail);
	void SpawnFood(std::optional<RectangleBuff> buff);
	std::optional<RectangleBuff> GetFoodBuff() const;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::FloatRect GetBounds();

private:
	sf::Vector2f m_initJail;
	sf::Vector2f m_endJail;
	sf::RectangleShape m_shape = sf::RectangleShape(sf::Vector2f(20.f, 20.f));
	sf::Vector2f getRandomValue(sf::Vector2f min, sf::Vector2f max, float gridShape);
	std::optional<RectangleBuff> m_buff;
};