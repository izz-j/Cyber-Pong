#include "StateManager.hpp"
#include <iostream>

StateManager::StateManager()
{
    std::cout << "StateManager constructed" << std::endl;
}
StateManager::~StateManager()
{
    std::cout << "StateManager destroyed" << std::endl;
}
std::string StateManager::GetID(State currentState)
{
    id = currentState.SetID();
}
void StateManager::AddState(State& currentState)
{
    if (!addedStates.empty())
	{
	    //do something
	}
    else
    addedStates.insert(std::pair<State*, std::string>(currentState, id));
}
