#include "states/GameWorld.h"
#include "states/MainMenu.h"

GameWorld::GameWorld(std::shared_ptr<Context>& context): m_context(context) {};

GameWorld::~GameWorld() {};

void GameWorld::Ready() 
{
	m_walls[0].setSize(sf::Vector2f(1000, 20));
	m_walls[0].setFillColor(sf::Color::White);
	m_walls[0].setPosition(sf::Vector2f(140, 120));

	m_walls[1].setSize(sf::Vector2f(20, 560));
	m_walls[1].setFillColor(sf::Color::White);
	m_walls[1].setPosition(sf::Vector2f(140, 120));

	m_walls[2].setSize(sf::Vector2f(1000, 20));
	m_walls[2].setFillColor(sf::Color::White);
	m_walls[2].setPosition(sf::Vector2f(140, 660));

	m_walls[3].setSize(sf::Vector2f(20, 560));
	m_walls[3].setFillColor(sf::Color::White);
	m_walls[3].setPosition(sf::Vector2f(1140, 120));

	m_snake.Ready(sf::Vector2f(1000, 140), sf::Vector2f(160, 140), sf::Vector2f(1120, 640));
	m_food.Ready(sf::Vector2f(160, 140), sf::Vector2f(1120, 640));
};

void GameWorld::Process(std::optional<sf::Event> event) 
{
	if (event && event->is<sf::Event::KeyPressed>())
	{
		switch (event->getIf<sf::Event::KeyPressed>()->code)
		{
		case sf::Keyboard::Key::Escape:
			m_context->states->AddState(std::make_unique<MainMenu>(m_context), true);
			break;
		default:
			break;
		};
	};

	m_snake.Process(event);
};

void GameWorld::PhysicsProcess(float delta) 
{
	m_snake.PhysicsProcess(delta);

	sf::FloatRect snakeHeadCollision = m_snake.GetHeadBounds();
	std::vector<sf::FloatRect> snakeBodyCollision = m_snake.GetBodyBounds();

	if (snakeBodyCollision.size() > 1)
	{
		for (auto& part : snakeBodyCollision)
		{
			if (part.findIntersection(snakeHeadCollision))
			{
				m_context->states->AddState(std::make_unique<MainMenu>(m_context), true);
			}
		}
	}

	if (snakeHeadCollision.findIntersection(m_food.GetBounds()))
	{
		m_snake.Grow();
		m_food.SpawnFood();
	}
};

void GameWorld::Draw() 
{
	m_context->window->clear();

	m_context->window->draw(m_snake);
	m_context->window->draw(m_food);

	for (auto& wall : m_walls)
	{
		m_context->window->draw(wall);
	}

	m_context->window->display();
};

void GameWorld::Start() {};
void GameWorld::Pause() {};