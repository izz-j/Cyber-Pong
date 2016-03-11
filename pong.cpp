//Author:Iseman Johnson
//First Pong game
#include <iostream>
#include <math.h>//for sine and cosine
#include <stdlib.h> //for srand and rand
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <unistd.h>//This is to use sleep(). This is temporary and for debugging purposes

void ball_traits(sf::RectangleShape& ball, sf::RectangleShape& leftPaddle, sf::RectangleShape& rightPaddle, int direction, sf::Clock& clock);
int ball_collision(sf::RectangleShape& ball, sf::RectangleShape& leftPaddle, sf::RectangleShape& rightPaddle, int& direction);


int main()
{
int direction = -1;
 sf::Clock clock;
  const int gameWidth = 800;
  const int gameHeight = 600;
  std::srand(time(0));
  sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "Pong!");
  window.setFramerateLimit(60);
  //Create left paddle (player's paddle)
  sf::RectangleShape leftPaddle(sf::Vector2f(20, 100));
    leftPaddle.setFillColor(sf::Color::Green);
    leftPaddle.setPosition(20, 200);
    //Create right paddle (AI)
    sf::RectangleShape rightPaddle(sf::Vector2f(20, 100));
    rightPaddle.setFillColor(sf::Color::Green);
    rightPaddle.setPosition(760, 200);
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
	ball_traits(ball, leftPaddle, rightPaddle, direction, clock);
	ball_collision(ball, leftPaddle, rightPaddle, direction);
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
void ball_traits(sf::RectangleShape& ball, sf::RectangleShape& leftPaddle, sf::RectangleShape& rightPaddle, int direction, sf::Clock& clock)
{
  //So my error was I had to add asSeconds() to make the ball go faster
  float elapsed= clock.getElapsedTime().asSeconds();
  bool stop = true;
  float pi = 3.1415;
  float ballSpeed = 1;
    //convert angle to radians
  float angle = 0;
      angle *= pi/180;
    //Scale X and Y will give the angle
    float scaleX = cos(angle);
    float scaleY = sin(angle);
    float velocityX = scaleX * ballSpeed;
    float velocityY = scaleY * ballSpeed;

    //so the problem was time!!! ?
    float moveX = velocityX * elapsed;
      float moveY = velocityY * elapsed;
	//I changed it to .move() again. I understand it better now
      //made it negative to go in the x direction

      //std::cout << direction << std::endl;
    if(direction == 1)
    {
        ball.move(moveX, -moveY);
	std::cout << elapsed << std::endl;
    }
    else if(direction == -1)
    {
        ball.move(-moveX , moveY);
	  std::cout << elapsed << std::endl;
    }
       //prevent the ball from going out of bounds
	if (ball.getPosition().x < leftPaddle.getPosition().x || ball.getPosition().x > rightPaddle.getPosition().x)
	 {
	   //Press space bar to throw the ball again
	    while (stop == true)
	     {
	       if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	        {
		   ball.setPosition(250, 200);
		   clock.restart();
		   stop = false;
		 }
	     }
	 }

int ball_collision(sf::RectangleShape& ball, sf::RectangleShape& leftPaddle, sf::RectangleShape& rightPaddle, int& direction)
{
    if(ball.getGlobalBounds().intersects(leftPaddle.getGlobalBounds()))
    {
        direction = 1;
        return direction;
    }
    else if(ball.getGlobalBounds().intersects(rightPaddle.getGlobalBounds()))
    {
        direction = -1;
        return direction;
    }
    else if(ball.getPosition().y < 1 || ball.getPosition().y > 580)
    {
        direction *= -1;
        return direction;
    }
    else
        return direction;

}
