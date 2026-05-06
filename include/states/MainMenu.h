#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "core/Game.h"
#include "core/GameContext.h"
#include "core/GameState.h"


class MainMenu : public GameState
{
public:
	MainMenu(std::shared_ptr<GameContext>& context);
	~MainMenu();

	void Ready() override;
	void Process(std::optional<sf::Event> event) override;
	void PhysicsProcess(float delta) override;
	void Draw() override;
	void Start() override;
	void Pause() override;

private:
	std::shared_ptr<GameContext> m_context;

	sf::Font m_tFont = sf::Font("assets/fonts/SmoochSans-VariableFont_wght.ttf");
	sf::Text m_gameTitle = sf::Text(m_tFont, "Retro Snake Game", 50);
	sf::Text m_btnPlay = sf::Text(m_tFont, "Start Game", 40);
	sf::Text m_btnExit = sf::Text(m_tFont, "Exit Game", 40);

	sf::Color m_btnSelectedColor = sf::Color::Yellow;
	sf::Color m_btnUnselectedColor = sf::Color::White;

	bool m_btnPlaySelected = true;
	bool m_btnPlayPressed = false;

	bool m_btnExitSelected = false;
	bool m_btnExitPressed = false;
};