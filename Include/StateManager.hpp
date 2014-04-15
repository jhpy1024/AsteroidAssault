#ifndef STATE_MANAGER_HPP
#define STATE_MANAGER_HPP

#include "State.hpp"

#include <stack>
#include <memory>

class StateManager
{
public:
	static StateManager& getInstance();

	void push(std::shared_ptr<State> state);
	void pop();
	void clear();
	void clearAndPush(std::shared_ptr<State> state);

	std::shared_ptr<State> top();

	bool empty() const;

private:
	StateManager() = default;

private:
	static std::unique_ptr<StateManager> m_Instance;

	std::stack<std::shared_ptr<State>> m_States;
};

#endif