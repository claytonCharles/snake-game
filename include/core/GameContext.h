#pragma once

#include <SFML/Graphics.hpp>
#include "GameStateManager.h"

struct GameContext
{
	std::unique_ptr<sf::RenderWindow> window;
	std::unique_ptr<GameStateManager> states;

	GameContext()
	{
		window = std::make_unique<sf::RenderWindow>();
		states = std::make_unique<GameStateManager>();
	}
};