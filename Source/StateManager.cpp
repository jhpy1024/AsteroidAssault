#include "StateManager.hpp"

#include <cassert>

std::unique_ptr<StateManager> StateManager::m_Instance;

StateManager& StateManager::getInstance()
{
	if (m_Instance == nullptr)
		m_Instance = std::unique_ptr<StateManager>(new StateManager);

	return *m_Instance;
}

void StateManager::push(std::shared_ptr<State> state)
{
	m_States.push(state);
	m_States.top()->init();
}

void StateManager::pop()
{
	m_States.pop();
}

void StateManager::clear()
{
	while (!m_States.empty())
	{
		m_States.pop();
	}
}

void StateManager::clearAndPush(std::shared_ptr<State> state)
{
	clear();
	push(state);
}

std::shared_ptr<State> StateManager::top()
{
	assert(!empty());
	return m_States.top();
}

bool StateManager::empty() const
{
	return m_States.empty();
}