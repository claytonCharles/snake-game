#include "GameStateManager.h"

GameStateManager::GameStateManager(): m_add(false), m_replace(false), m_remove(false) {};

GameStateManager::~GameStateManager() {};

void GameStateManager::AddState(std::unique_ptr<GameState> toAdd, bool replace)
{
	m_add = true;
	m_newState = std::move(toAdd);
	m_replace = replace;
};

void GameStateManager::PopCurrent() 
{
	m_remove = true;
};

void GameStateManager::ProcessStateChange() 
{
	if (m_remove && !m_statesStack.empty())
	{
		m_statesStack.pop();
		
		if (!m_statesStack.empty())
		{
			m_statesStack.top()->Ready();
		}

		m_remove = false;
	}

	if (m_add)
	{
		if (m_replace && !m_statesStack.empty())
		{
			m_statesStack.pop();
		}

		if (!m_statesStack.empty())
		{
			m_statesStack.top()->Pause();
		}

		m_statesStack.push(std::move(m_newState));
		m_statesStack.top()->Ready();
		m_replace = false;
		m_add = false;
	}
};


std::unique_ptr<GameState>& GameStateManager::GetCurrentState() 
{
	return m_statesStack.top();
};