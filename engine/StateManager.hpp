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
    void  StampID(State& currentState);
    //Add State
    void AddState(State& currentState);
    //Switch State
    void SwitchState(State& currentState);
    //Remove State
    void RemoveState();
  
    
private:
    //Time until switch flag
    bool ready;
    //string id
    int indexId = 1;
    int id;
    
    //Make a map of state pointers and string key values
    typedef std::map<State*, std::string> StateMap;
    //iterator
    std::map<State*, std::string>::iterator itr;

    //All states will be added to this map
    StateMap activeState;
    
    //May not serve a purpose anymore....
    StateMap deactiveStates;
};
#endif
