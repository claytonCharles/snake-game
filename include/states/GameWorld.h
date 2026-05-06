#pragma once

#include "core/Game.h"
#include "core/GameContext.h"
#include "core/GameState.h"
#include "entities/Snake.h"
#include "entities/Food.h"

class GameWorld : public GameState
{
public:
	GameWorld(std::shared_ptr<GameContext>& context);
	~GameWorld();

	void Ready() override;
	void Process(std::optional<sf::Event> event) override;
	void PhysicsProcess(float delta) override;
	void Draw() override;
	void Start() override;
	void Pause() override;

private:
	std::shared_ptr<GameContext> m_context;
	std::array<sf::RectangleShape, 4> m_walls;

	sf::Font m_tFont = sf::Font("assets/fonts/SmoochSans-VariableFont_wght.ttf");
	sf::Text m_gameScore = sf::Text(m_tFont, "Score: 0", 30);

	int m_score = 0;

	Snake m_snake;
	Food m_food;
};