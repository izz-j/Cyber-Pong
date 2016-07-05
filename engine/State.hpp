#ifndef STATE_HPP
#define STATE_HPP

#include <SFML/Graphics.hpp> 
#include <string>
class State
{
public:

    State() : created(true){}
    ~State();

    //Set State ID
    virtual std::string SetID();
    //Setup State
    virtual void Setup();
    //Update state using time
    //later a flag will be added to this argument
    virtual void Update(sf::Time t);
    //Destroy it
    virtual void Destroy();

private:
    //active checks if state is active used for debugging
    bool created = false;
    sf::Time elapsed;
};
#endif
