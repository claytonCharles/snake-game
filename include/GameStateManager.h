#pragma once

#include <stack>
#include <memory>
#include <GameState.h>

class GameStateManager
{
public:
	GameStateManager();
	~GameStateManager();

	void AddState(std::unique_ptr<GameState> toAdd, bool replace = false);
	void PopCurrent();
	void ProcessStateChange();

	std::unique_ptr<GameState>& GetCurrentState();

private:
	std::stack<std::unique_ptr<GameState>> m_statesStack;
	std::unique_ptr<GameState> m_newState;

	bool m_add;
	bool m_replace;
	bool m_remove;
};