#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "Snake.h"
#include "Food.h"
#include "GameStateManager.h"

struct Context
{
	std::unique_ptr<sf::RenderWindow> window;
	std::unique_ptr<GameStateManager> states;

	Context()
	{
		window = std::make_unique<sf::RenderWindow>();
		states = std::make_unique<GameStateManager>();
	}
};

class Game
{
public:
	Game();
	~Game();

	void Run();

private:
	std::shared_ptr<Context> m_context;
	sf::Clock m_clock;
};