#pragma once

#include <iostream>
#include <optional>
#include <SFML/Window/Event.hpp>

class GameState
{
public:
	GameState() {};
	virtual ~GameState() {};

	virtual void Ready() = 0;
	virtual void Exit() = 0;
	virtual void Process(std::optional<sf::Event> event) = 0;
	virtual void PhysicsProcess(float delta) = 0;
	virtual void Draw() = 0;
	virtual void Start() {};
	virtual void Pause() {};
};