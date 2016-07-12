#ifndef INTRO_HPP
#define INTRO_HPP

#include "State.hpp"
#include <SFML/Graphics.hpp>
#include <string>

class Intro : public State
{
public:
    Intro();
    ~Intro();
    //set ID
    void SetID(int id);
    //Get ID
    int GetID()
    {return introID;}
    
    //load textures..
    void Setup();
    //update according to time
    void Update(sf::Time t);
    //Close it
    //Not so sure if I neeed this ..
    void Destroy();

protected:
    int introID;
    
private:
    sf::Texture introTexture;
    sf::Sprite intro;
    sf::Clock clock;
    
};
#endif
