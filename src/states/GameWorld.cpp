#include "core/GameContext.h"
#include "states/GameWorld.h"
#include "states/MainMenu.h"

GameWorld::GameWorld(std::shared_ptr<GameContext>& context): m_context(context) {};

GameWorld::~GameWorld() {};

void GameWorld::Ready() 
{
	m_bgMusic.play();
	m_bgMusic.setVolume(50);

	const sf::Vector2u screenSize = m_context->window->getSize();

	const float tileSize = 20.f;

	const int gridWidth = 48;
	const int gridHeight = 28;

	const float jailHeight = gridHeight * tileSize;
	const float jailWidth = gridWidth * tileSize;
	const float wallThickness = tileSize;

	const float initOffSetX = (screenSize.x - jailWidth) / 2.f;
	const float initOffSetY = (screenSize.y - jailHeight) / 2.f;

	const float endOffSetX = initOffSetX + jailWidth - wallThickness;
	const float endOffSetY = initOffSetY + jailHeight - wallThickness;

	const float startPositionX = initOffSetX + jailWidth / 2.f;
	const float startPositionY = initOffSetY + jailHeight / 2.f;

	const sf::Vector2f initJail = sf::Vector2f(initOffSetX + tileSize, initOffSetY + tileSize);
	const sf::Vector2f endJail = sf::Vector2f(endOffSetX - tileSize, endOffSetY - tileSize);

	m_gameScore.setStyle(sf::Text::Bold);
	m_gameScore.setFillColor(sf::Color(0, 255, 120));
	m_gameScore.setPosition(sf::Vector2f(40.f, 25.f));

	m_background = sf::RectangleShape (sf::Vector2f(gridWidth * tileSize, gridHeight * tileSize));
	m_background.setFillColor(sf::Color(20,20,20));
	m_background.setPosition(sf::Vector2f(initOffSetX, initOffSetY));

	drawWalls(jailWidth, jailHeight, initOffSetX, initOffSetY, tileSize);

	m_snake.Ready(sf::Vector2f(startPositionX, startPositionY), initJail, endJail);
	m_food.Ready(initJail, endJail);
};

void GameWorld::Exit() 
{
	m_bgMusic.stop();
}

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

	if (m_snake.CheckSelfCollision())
	{
		m_context->states->AddState(std::make_unique<MainMenu>(m_context), true);
	}

	if (snakeHeadCollision.findIntersection(m_food.GetBounds()))
	{
		RectangleBuff buff = m_buff.GetRandomBuff();
		std::optional<RectangleBuff> foodBuff = m_food.GetFoodBuff();

		m_snake.Grow(foodBuff);
		m_food.SpawnFood(buff);

		m_score += 1;
		m_gameScore.setString(std::format("Score: {}", m_score));
	}
};

void GameWorld::Draw() 
{
	m_context->window->clear();

	m_context->window->draw(m_background);
	m_context->window->draw(m_gameScore);
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

void GameWorld::drawWalls(float jailWidth, float jailHeight, float offsetX, float offsetY, float wallThickness)
{
	sf::Color wallColor(0, 180, 0);

	//TOP
	m_walls[0].setSize(sf::Vector2f(jailWidth, wallThickness));
	m_walls[0].setFillColor(wallColor);
	m_walls[0].setPosition(sf::Vector2f(offsetX, offsetY));

	// LEFT
	m_walls[1].setSize(sf::Vector2f(wallThickness, jailHeight));
	m_walls[1].setFillColor(wallColor);
	m_walls[1].setPosition(sf::Vector2f(offsetX, offsetY));

	// BOTTOM
	m_walls[2].setSize(sf::Vector2f(jailWidth, wallThickness));
	m_walls[2].setFillColor(wallColor);
	m_walls[2].setPosition(sf::Vector2f(offsetX, offsetY + jailHeight - wallThickness));

	// RIGHT
	m_walls[3].setSize(sf::Vector2f(wallThickness, jailHeight));
	m_walls[3].setFillColor(wallColor);
	m_walls[3].setPosition(sf::Vector2f(offsetX + jailWidth - wallThickness, offsetY));
}