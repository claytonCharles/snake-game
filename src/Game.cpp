#include "Game.h"
#include <iostream>

using namespace std;

Game::Game() : window(sf::VideoMode({ 800, 600 }), "Snake Game") 
{
	snake.setScreenSpace(sf::Vector2f(800, 600));
}

void Game::run()
{
	while (window.isOpen())
	{
		processEvents();
		update();
		render();
	}
}

void Game::processEvents()
{
	while (auto event = window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			window.close();
		}
	}
}

void Game::update()
{
	float delta = clock.restart().asSeconds();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		snake.updateDirection(sf::Vector2i(0, -1));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		snake.updateDirection(sf::Vector2i(-1, 0));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		snake.updateDirection(sf::Vector2i(0, 1));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		snake.updateDirection(sf::Vector2i(1, 0));
	}

	snake.update(delta);
}

void Game::render()
{
	window.clear();
	snake.draw(window);
	window.display();
}