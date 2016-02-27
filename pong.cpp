//Author:Iseman Johnson
//First Pong game
#include <iostream>
#include <stdlib.h> //for srand and rand
#include <SFML/Graphics.hpp>

void ball_traits(sf::RectangleShape ball, sf::RectangleShape leftPaddle);
int main()
{
  const int gameWidth = 500;
  const int gameHeight = 400;
  std::srand(time(0));
  
  sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "Pong!");
  //Create left paddle (player's paddle)
  sf::RectangleShape leftPaddle(sf::Vector2f(20, 100));
    leftPaddle.setFillColor(sf::Color::Green);
    leftPaddle.setPosition(10, 10);
    //Create right paddle (AI)
    sf::RectangleShape rightPaddle(sf::Vector2f(20, 100));
    rightPaddle.setFillColor(sf::Color::Green);
    rightPaddle.setPosition(470, 10);
    //Create the ball
    sf::RectangleShape ball(sf::Vector2f(20, 20));
    ball.setFillColor(sf::Color::Green);
    ball.setPosition(250, 200);
    
    //This is the game loop gameplay goes in here
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
	    //Player's Left Paddle movement
	//Up
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && leftPaddle.getPosition().y > gameHeight - 410)
      {
	//lets get the y axis values going up
	std::cout << leftPaddle.getPosition().y << std::endl; 
	leftPaddle.move(0 , -.2);
      }
	//Down
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && leftPaddle.getPosition().y < gameHeight - 100)
      {
	//let me get the y axis values going down
	std::cout << leftPaddle.getPosition().y << std::endl; 
	leftPaddle.move(0, .2);
      }	
	ball_traits(ball, leftPaddle);
	//clear
        window.clear();
	//draw
        window.draw(leftPaddle);
	window.draw(rightPaddle);
	window.draw(ball);
        window.display();
    }

    return 0;
}
void ball_traits(sf::RectangleShape ball, sf::RectangleShape leftPaddle)
{
  //Physics
	//Should be in seconds?
	// speed = distance moved/time
        //well if the ball is a square maybe I need to find the area? hmm
	int ballSpeed;
	double distanceX;
	double distanceY;
	double lspeedX = .2;
	double speedY = 0.0;
   
	//space to start ball this is mostly for testing purposes
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	  {
	    sf::Clock clock;
	sf::Time elapsed = clock.getElapsedTime();
	
	
	    //throw to the left
	//lspeedX = (10 - ball.getPosition().x)/elapsed.asSeconds();
	    // speedY = ball.getPosition().y/elapsed.asSeconds();
	while (ball.getPosition().x > leftPaddle.getPosition().x)
	  {
	    ball.move( speedY--, speedY);
	    std::cout <<lspeedX << std::endl;
	    std::cout << speedY << std::endl;
	  }
	  }
}
