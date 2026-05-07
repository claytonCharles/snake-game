#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "GameStateManager.h"
#include "GameContext.h"

class Game
{
public:
	Game();
	~Game();

	void Run();

private:
	std::shared_ptr<GameContext> m_context;
	sf::Clock m_clock;
};