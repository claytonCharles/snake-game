#include "core/Game.h"
#include "core/GameContext.h"
#include "states/MainMenu.h"
#include <iostream>
#include <optional>

using namespace std;

Game::Game() : m_context(std::make_shared<GameContext>())
{
	m_context->window->create(sf::VideoMode({ 1280, 720 }), "Snake Game By Clayton Charlers", sf::Style::Close);
	m_context->states->AddState(std::make_unique<MainMenu>(m_context));
}

Game::~Game() {}

void Game::Run()
{
	while (m_context->window->isOpen())
	{
		while (auto event = m_context->window->pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				m_context->window->close();
			}

			m_context->states->ProcessStateChange();
			m_context->states->GetCurrentState()->Process(event);
		}

		float delta = m_clock.restart().asSeconds();
		m_context->states->GetCurrentState()->PhysicsProcess(delta);
		m_context->states->GetCurrentState()->Draw();
	}
}