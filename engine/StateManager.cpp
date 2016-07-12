#include "StateManager.hpp"
#include <iostream>

//cout statements are for debug purposes

StateManager::StateManager()
{
    std::cout << "StateManager constructed." << std::endl;
}
StateManager::~StateManager()
{
    std::cout << "StateManager destroyed." << std::endl;
}

void  StateManager::StampID(State& currentState)
{
    currentState.SetID(indexId);
    indexId++;
    
}
void StateManager::AddState(State& currentState)
{
    
    if (!activeState.empty())
	{
	    //do something	    
	    RemoveState();
	}

    id = currentState.GetID();

    activeState.insert(std::pair<State*, std::string>(currentState, id));
    //Output the ID of the state
    std::cout << "Added state: "<< activeState[currentState] << " to the activeStates StateMap." << std::endl;
}
//maybe this should have another argument with the state
//it is being switched to
void StateManager::SwitchState(State& currentState)
{
    if (addedStates.empty())
	{
	    ready = false;
	    AddState(currentState);
	}
	//do something
    ready = true;

}
void StateManager::RemoveState(State& currentState)
{
    deactiveStates
}
