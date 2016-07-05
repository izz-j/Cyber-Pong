#ifndef STATEMANAGER_HPP
#define STATEMANAGER_HPP

#include "State.hpp"
#include <vector>
#include <string>
#include <map>
#include <utility> 


class StateManager : public State
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
    //Time until switch flag
    bool ready;
    //string id
    std::string id;
    
    //Make a map of state pointers and string key values
    typedef std::map<State*, std::string> StateMap;
    
    //All states will be added to this map
    StateMap addedStates;
    //All states will be removed from StatesAdded
    //To removed States
    StateMap removedStates;
};
#endif
