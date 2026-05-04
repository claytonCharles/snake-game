#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "Snake.h"

class Game
{
public:
	Game();
	void run();


private:
	void processEvents();
	void update();
	void render();


	sf::RenderWindow window;
	sf::Clock clock;

	Snake snake;

};