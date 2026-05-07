#include "entities/Snake.h"
#include <typeinfo>
#include <algorithm>

Snake::Snake() {};

void Snake::Ready(sf::Vector2f initPosition, sf::Vector2f initJail, sf::Vector2f endJail)
{
	m_initJail = initJail;
	m_endJail = endJail;

	m_head.setFillColor(sf::Color::Blue);
	m_head.setPosition(initPosition);
	m_direction = { 0, 1 };
}

void Snake::Process(std::optional<sf::Event> event)
{
	if (event && event->is<sf::Event::KeyPressed>())
	{
		sf::Keyboard::Key keyCode = event->getIf<sf::Event::KeyPressed>()->code;
		if (keyCode == sf::Keyboard::Key::W || keyCode == sf::Keyboard::Key::Up)
		{
			updateDirection(sf::Vector2i(0, -1));
		}
		if (keyCode == sf::Keyboard::Key::A || keyCode == sf::Keyboard::Key::Left)
		{
			updateDirection(sf::Vector2i(-1, 0));
		}
		if (keyCode == sf::Keyboard::Key::S || keyCode == sf::Keyboard::Key::Down)
		{
			updateDirection(sf::Vector2i(0, 1));
		}
		if (keyCode == sf::Keyboard::Key::D || keyCode == sf::Keyboard::Key::Right)
		{
			updateDirection(sf::Vector2i(1, 0));
		}
	}
}

void Snake::PhysicsProcess(float delta)
{

	m_timer += delta;
	if (m_buff && m_buff.value().randomBuff == EBuffs::Speed)
	{
		if (m_buffDuration > 0.f)
		{
			m_buffDuration -= delta;
		}
		else
		{
			m_buff = std::nullopt;
			m_delay = 0.1f;
			m_buffDuration = 0.f;
		}
	}

	if (m_timer >= m_delay)
	{
		m_timer = 0.f;
		move(delta);
	}
}

void Snake::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(m_head);

	for (auto& segment : m_body)
	{
		target.draw(segment);
	}
}

void Snake::move(float delta)
{
	sf::Vector2f currentPosition = m_head.getPosition();
	Snake::moveSnakeHead(currentPosition, delta);

	if (m_body.size() > 0)
	{
		for (int i = 0; i <= m_body.size() - 1; i++)
		{
			sf::Vector2f targetPosition = currentPosition;
			currentPosition = m_body[i].getPosition();
			m_body[i].setPosition(targetPosition);
		}
	}
}

void Snake::Grow(std::optional<RectangleBuff> buff)
{
	sf::Vector2f lastPosition;
	sf::Color segmentColor = sf::Color::Green;
	if (m_body.size() >= 1)
	{
		int lastPart = m_body.size() - 1;
		lastPosition = m_body[lastPart].getPosition();
	}
	else
	{
		lastPosition = m_head.getPosition();
	}

	sf::RectangleShape segment(m_head.getSize());


	if (buff)
	{
		RectangleBuff current = buff.value();
		segmentColor = current.rectColor;
		if (current.randomBuff == EBuffs::Speed)
		{
			m_buff = buff;
			m_delay = 0.050f;
			m_buffDuration += 5.f;
		}

		if (current.randomBuff == EBuffs::UpSize)
		{
			sf::RectangleShape segmentAdd(m_head.getSize());
			segmentAdd.setFillColor(sf::Color::Green);
			segmentAdd.setPosition(lastPosition);
			m_body.push_back(segment);

			lastPosition = m_body[m_body.size() - 1].getPosition();
		}

		if (current.randomBuff == EBuffs::DownSize)
		{
			int bodySplit = m_body.size() > 3 ? 3 : 1;
			m_body.resize(m_body.size() - bodySplit);
		}
	}

	segment.setFillColor(segmentColor);
	segment.setPosition(lastPosition);
	m_body.push_back(segment);
}

sf::FloatRect Snake::GetHeadBounds()
{
	return m_head.getGlobalBounds();
}

std::vector<sf::FloatRect> Snake::GetBodyBounds()
{
	std::vector<sf::FloatRect> bounds;
	for (auto& segment : m_body)
	{
		bounds.push_back(segment.getGlobalBounds());
	}

	return bounds;
}

void Snake::updateDirection(sf::Vector2i targetDirection)
{
	if (m_direction.x != 0 && targetDirection.x != 0) return;
	if (m_direction.y != 0 && targetDirection.y != 0) return;
	m_direction = targetDirection;
}

void Snake::moveSnakeHead(sf::Vector2f currentPosition, float delta)
{
	currentPosition.x += m_direction.x * m_snakeBodyBox;
	currentPosition.y += m_direction.y * m_snakeBodyBox;

	if (currentPosition.x <= m_initJail.x - m_snakeBodyBox)
	{
		currentPosition.x = m_endJail.x;
	}

	if (currentPosition.x >= m_endJail.x + m_snakeBodyBox)
	{
		currentPosition.x = m_initJail.x;
	}

	if (currentPosition.y <= m_initJail.y - m_snakeBodyBox)
	{
		currentPosition.y = m_endJail.y;
	}

	if (currentPosition.y >= m_endJail.y + m_snakeBodyBox)
	{
		currentPosition.y = m_initJail.y;
	}

	m_head.setPosition(currentPosition);
}