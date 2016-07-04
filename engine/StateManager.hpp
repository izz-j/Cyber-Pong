#ifndef STATEMANAGER_HPP
#define STATEMANAGER_HPP

#include "State.hpp"
#include <vector>
#include <string>


class StateManager
{
public:
    StateManager();
    ~StateManager();

     //This will track the state
    //shhould be helpful for debug purposes
    std::string GetID(State currentState);
    //Add State
    void AddState(State& currentState);
    //Switch State
    void SwitchState(State& currentState);
    //Remove State
    void RemoveState(State& currentState);
  
    
private:
    //String ID
    std::string id;
    //Time until switch flag
    bool ready;
    //All states will be added to this vector
    std::vector<State*> addedStates;
    //All states will be removed from StatesAdded
    //To removed States
    std::vector<State*> removedStates
};
#endif
