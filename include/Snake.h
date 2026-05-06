#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class Snake : public sf::Drawable
{
public:
	Snake();

	void Ready(sf::Vector2f initPosition, sf::Vector2f initJail, sf::Vector2f endJail);
	void Process(std::optional<sf::Event> event);
	void PhysicsProcess(float delta);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void Grow();

	sf::FloatRect GetHeadBounds();
	std::vector<sf::FloatRect> GetBodyBounds();

private:
	sf::RectangleShape m_head = sf::RectangleShape(sf::Vector2f(20.f, 20.f));

	std::vector<sf::RectangleShape> m_body;

	sf::Vector2f m_initJail;
	sf::Vector2f m_endJail;
	sf::Vector2i m_direction;

	float m_timer = 0.f;
	float m_delay = 0.1f;
	float m_snakeBodyBox = 20.f;

	void move(float delta);
	void moveSnakeHead(sf::Vector2f currentPosition, float delta);
	void updateDirection(sf::Vector2i direction);
};