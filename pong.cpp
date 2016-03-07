//Author:Iseman Johnson
//First Pong game
#include <iostream>
#include <math.h>//for sine and cosine
#include <stdlib.h> //for srand and rand
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <unistd.h>//This is to use sleep(). This is temporary and for debugging purposes

void ball_traits(sf::RenderWindow& window,sf::Clock clock, sf::RectangleShape& ball, sf::RectangleShape& leftPaddle, sf::RectangleShape& rightPaddle);

int main()
{
 sf::Clock clock;
  const int gameWidth = 800;
  const int gameHeight = 600;
  std::srand(time(0));
  sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "Pong!");
  window.setFramerateLimit(65); 
  //Create left paddle (player's paddle)
  sf::RectangleShape leftPaddle(sf::Vector2f(20, 100));
    leftPaddle.setFillColor(sf::Color::Green);
    leftPaddle.setPosition(20, 10);
    //Create right paddle (AI)
    sf::RectangleShape rightPaddle(sf::Vector2f(20, 100));
    rightPaddle.setFillColor(sf::Color::Green);
    rightPaddle.setPosition(760, 10);
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
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && leftPaddle.getPosition().y > 0)
      {
	//lets get the y axis values going up
	//std::cout << "Position: "<<  leftPaddle.getPosition().y << std::endl;
	leftPaddle.move(0 , -10);
      }
	//Down
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && leftPaddle.getPosition().y < gameHeight - 100)
      {
	//let me get the y axis values going down
	//std::cout << "Position: " << leftPaddle.getPosition().y << std::endl; 
	leftPaddle.move(0, 10);
      }
	//Ball Physics
	ball_traits(window, clock, ball, leftPaddle, rightPaddle);
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
void ball_traits(sf::RenderWindow& window, sf::Clock clock, sf::RectangleShape& ball, sf::RectangleShape& leftPaddle, sf::RectangleShape& rightPaddle)
{
  bool countFinished = false;
  float pi = 3.1415;
  float ballSpeed = 1;
    //convert angle to radians
  int angle = 0;
      angle *= pi/180;
    //Scale X and Y will give the angle
    float scaleX = cos(angle);
    //std::cout << scaleX << std::endl;
    float scaleY = sin(angle);
    float velocityX = scaleX * ballSpeed;
    float velocityY = scaleY * ballSpeed;
    //take original position
    float posX = ball.getPosition().x;
    float posY = ball.getPosition().y;
	  
    float elapsed = clock.restart().asSeconds();
    //std::cout << elapsed << std::endl; 
    float moveX = velocityX  * elapsed;
    float moveY = velocityY * elapsed;
	//std::cout << moveX << std::endl;
	//std::cout << moveY << std::endl;
	//I think I like this better than .move()
	ball.setPosition(posX - moveX, posY - moveY);
       //prevent the ball from going out of bounds
	//std::cout << "Ball position: " <<  ball.getPosition().x << std::endl;
       if (ball.getPosition().x < leftPaddle.getPosition().x || ball.getPosition().x > rightPaddle.getPosition().x)
	 {
	   //Timer here, Hold the ball for a few seconds before releasing it
	   //ughh can't compare floats
	   /* while (countFinished == false)
	     {
	       
	       sf::Clock timer;
	       sf::Time count;
	        count = timer.getElapsedTime();
	      std::cout << count.asSeconds() << std::endl;
	      if (count.asSeconds() >= 0.1f)
	        {
		   countFinished = true;
		 }
	     }
	       */
	     ball.setPosition(250, 200);
	     clock.restart().asSeconds();
	 }
       if (ball.getPosition().y <= 0)
           ball.move(250, 200);
}
