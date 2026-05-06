#pragma once

#include "Game.h"
#include "GameState.h"
#include "Snake.h"
#include "Food.h"

class GameWorld : public GameState
{
public:
	GameWorld(std::shared_ptr<Context>& context);
	~GameWorld();

	void Ready() override;
	void Process(std::optional<sf::Event> event) override;
	void PhysicsProcess(float delta) override;
	void Draw() override;
	void Start() override;
	void Pause() override;

private:
	std::shared_ptr<Context> m_context;
	std::array<sf::RectangleShape, 4> m_walls;

	Snake m_snake;
	Food m_food;
};