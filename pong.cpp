//Author:Iseman Johnson
//First Pong game
#include <iostream>
#include <math.h>//for sine and cosine
#include <stdlib.h> //for srand and rand
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp> 

void ball_traits(sf::Clock clock, sf::RectangleShape& ball, sf::RectangleShape leftPaddle);

int main()
{
  sf::Clock clock;
  const int gameWidth = 500;
  const int gameHeight = 400;
  std::srand(time(0));
  sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "Pong!");
  window.setFramerateLimit(60); 
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
	//std::cout << "Position: "<<  leftPaddle.getPosition().y << std::endl; 
	leftPaddle.move(0 , -.2);
      }
	//Down
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && leftPaddle.getPosition().y < gameHeight - 100)
      {
	//let me get the y axis values going down
	//std::cout << "Position: " << leftPaddle.getPosition().y << std::endl; 
	leftPaddle.move(0, .2);
      }
	//Ball Physics
	ball_traits(clock, ball, leftPaddle);
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
void ball_traits(sf::Clock clock, sf::RectangleShape& ball, sf::RectangleShape leftPaddle)
{
  double pi = 3.1415;
    double ballSpeed = 10;
    int angle = 30 * pi/180;
    //Scale X and Y will give the angle
    double scaleX = cos(angle);
    //std::cout << scaleX << std::endl;
    double scaleY = sin(angle);
    double velocityX = scaleX * ballSpeed;
    double velocityY = scaleY * ballSpeed;
    //take original position
    double moveX = ball.getPosition().x;
    double moveY = ball.getPosition().y;
	  
    double elapsed = clock.restart().asSeconds();
    std::cout << elapsed << std::endl; 
    //    while (ball.getPosition().x > 10 && ball.getPosition().y > 10)
    // {
	    moveX += velocityX  * elapsed;
	    moveY += velocityY * elapsed;
	    std::cout << moveX << std::endl;
	    std::cout << moveY << std::endl;
            ball.move(moveX,  moveY);
	    ball.setPosition(moveX, moveY);
	    //  }
      
	 
}
