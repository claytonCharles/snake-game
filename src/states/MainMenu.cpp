#include "core/GameContext.h"
#include "states/MainMenu.h"
#include "states/GameWorld.h"
#include <iostream>

MainMenu::MainMenu(std::shared_ptr<GameContext>& context) : m_context(context) {};

MainMenu::~MainMenu() {};

void MainMenu::Ready()
{
	float windowCenterX = m_context->window->getSize().x / 2.f;
	float windowCenterY = m_context->window->getSize().y / 2.f;

	m_gameTitle.setStyle(sf::Text::Bold);
	m_gameTitle.setPosition(sf::Vector2f(windowCenterX - m_gameTitle.getLocalBounds().getCenter().x, 0));

	sf::Vector2f playCenter = m_btnPlay.getLocalBounds().getCenter();
	sf::Vector2f exitCenter = m_btnExit.getLocalBounds().getCenter();

	m_btnPlay.setPosition(sf::Vector2f(windowCenterX - playCenter.x, windowCenterY - playCenter.y));
	m_btnPlay.setStyle(sf::Text::Bold);
	m_btnExit.setPosition(sf::Vector2f(windowCenterX - exitCenter.x, windowCenterY - exitCenter.y + 50));
	m_btnExit.setStyle(sf::Text::Bold);
}

void MainMenu::Process(std::optional<sf::Event> event)
{
	
	if (event && event->is<sf::Event::KeyPressed>())
	{
		switch (event->getIf<sf::Event::KeyPressed>()->code)
		{
		case sf::Keyboard::Key::W:
			m_btnPlaySelected = true;
			m_btnExitSelected = false;
			break;
		case sf::Keyboard::Key::S:
			m_btnPlaySelected = false;
			m_btnExitSelected = true;
			break;
		case sf::Keyboard::Key::Enter:
			m_btnPlayPressed = m_btnPlaySelected;
			m_btnExitPressed = m_btnExitSelected;
			break;
		}
	}

	m_btnPlay.setFillColor(m_btnPlaySelected ? m_btnSelectedColor : m_btnUnselectedColor);
	m_btnExit.setFillColor(m_btnExitSelected ? m_btnSelectedColor : m_btnUnselectedColor);

	if (m_btnPlayPressed)
	{
		m_context->states->AddState(std::make_unique<GameWorld>(m_context));
	}

	if (m_btnExitPressed)
	{
		m_context->window->close();
	}
}

void MainMenu::PhysicsProcess(float delta)
{

}

void MainMenu::Draw()
{
	m_context->window->clear();
	m_context->window->draw(m_gameTitle);
	m_context->window->draw(m_btnPlay);
	m_context->window->draw(m_btnExit);
	m_context->window->display();
}

void MainMenu::Start() {};
void MainMenu::Pause() {};