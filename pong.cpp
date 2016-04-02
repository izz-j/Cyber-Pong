//Authors: Iseman Johnson 
//First Pong game
#include <iostream>
#include <math.h>//for sine and cosine
#include <stdlib.h> //for srand and rand
#include <SFML/Graphics.hpp>//for graphics
#include <SFML/Audio.hpp> //for sound

  float pi = 3.1415;
void ball_traits(sf::RectangleShape& ball, sf::RectangleShape& leftPaddle, sf::RectangleShape& rightPaddle, int& direction, sf::Clock& clock, float& angle, sf::Sound& blip);
int paddle_collision(const int& paddleSizeY, sf::RectangleShape& ball, sf::RectangleShape& leftPaddle, sf::RectangleShape& rightPaddle, int& direction, float& angle, sf::Sound& blip);
void ai_paddle(sf::RectangleShape& ball, sf::RectangleShape& rightPaddle,  int& direction, sf::Clock& clock, const int& gameHeight); 

int main()
{
int direction = -1;
 sf::Clock clock;
  const int gameWidth = 800;
  const int gameHeight = 600;
  std::srand(time(0));
  sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "Pong!");
  window.setFramerateLimit(65);
  //Create left paddle (player's paddle)
   const int paddleSizeY = 100;
  sf::RectangleShape leftPaddle(sf::Vector2f(20, paddleSizeY));
    leftPaddle.setFillColor(sf::Color::Green);
    leftPaddle.setPosition(20, 200);
    //Create right paddle (AI)
    sf::RectangleShape rightPaddle(sf::Vector2f(20, paddleSizeY));
    rightPaddle.setFillColor(sf::Color::Green);
    rightPaddle.setPosition(760, 200);
    //Create the ball
    sf::RectangleShape ball(sf::Vector2f(20, 20));
    ball.setFillColor(sf::Color::Green);
    ball.setPosition(250, 200);
    //ball initial angle
     float angle = 0;
     //load sound
     sf::SoundBuffer blipBuffer;
     if (!blipBuffer.loadFromFile("audio/pongblip.wav"))
	 return -1;
     sf::Sound blip;
     blip.setBuffer(blipBuffer);
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
	ball_traits(ball, leftPaddle, rightPaddle, direction, clock, angle, blip);
	paddle_collision(paddleSizeY, ball, leftPaddle, rightPaddle, direction, angle, blip);
	ai_paddle(ball, rightPaddle,  direction, clock, gameHeight);
	//std::cout << ball.getPosition().y << std::endl;
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
void ball_traits(sf::RectangleShape& ball, sf::RectangleShape& leftPaddle, sf::RectangleShape& rightPaddle, int& direction, sf::Clock& clock, float& angle, sf::Sound& blip)
{
  //So my error was I had to add asSeconds() to make the ball go faster
  float elapsed= clock.getElapsedTime().asSeconds();
  bool stop = true;
  float ballSpeed = 1;
    float scaleX = cos(angle * pi/180);
    float scaleY = sin(angle * pi/180);
    // std::cout << angle << std::endl;
    float velocityX = scaleX * ballSpeed;
    float velocityY = scaleY * ballSpeed;
    float moveX = velocityX;
    float moveY = velocityY;
    
    //Cap the speed by freezing time
    if (elapsed >= 10.f)
      {
	elapsed = 10.f;
      }
    if(direction == 1)
    {
	ball.move(moveX * elapsed, moveY * elapsed);
	//std::cout << elapsed << std::endl;
    }
    else if(direction == -1)
    {
	ball.move(-moveX * elapsed, moveY * elapsed );
	// std::cout << elapsed << std::endl;
    }
    //top and bottom collisions
     if (ball.getPosition().y < 2.f)
	{
	    blip.play();
	    angle = -angle;
	    ball.move(moveX, -moveY * elapsed);
	}
    else if (ball.getPosition().y > 578.f)
	{
	    blip.play();
	    angle = -angle;
	    ball.move(moveX, -moveY * elapsed);
	    }
	    
    
       //prevent the ball from going out of  bounds passed the paddle
	if (ball.getPosition().x < leftPaddle.getPosition().x || ball.getPosition().x > rightPaddle.getPosition().x)
	 {
	   //Press space bar to throw the ball again
	    while (stop == true)
	     {
	       if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	        {
		   ball.setPosition(250, 200);
		   leftPaddle.setPosition(20, 200);
		   rightPaddle.setPosition(760,  200);
		   angle = 0;
		   direction = 1;
		   clock.restart();
		   stop = false;
		 }
	     }
	 }
}

int paddle_collision(const int& paddleSizeY, sf::RectangleShape& ball, sf::RectangleShape& leftPaddle, sf::RectangleShape& rightPaddle, int& direction, float& angle, sf::Sound& blip)
{
    if (ball.getGlobalBounds().intersects(leftPaddle.getGlobalBounds()))
	{
	    blip.play();
	    direction = 1;
	    //std::cout << ball.getPosition().y << std::endl;
	    if (ball.getPosition().y < leftPaddle.getPosition().y + 30)
		{
		    std::cout << "Hitting the top left" << std::endl;
		    angle = (rand() % 35 + 30);
		    angle = -angle;
		}
	    else if (ball.getPosition().y >  leftPaddle.getPosition().y + 30 && ball.getPosition().y < leftPaddle.getPosition().y + 50)
		{
		    std::cout << "hitting left middle" << std::endl;
		    angle = 0;
		}
	    else if (ball.getPosition().y >  leftPaddle.getPosition().y  + 50)
		{
		    std::cout << "hitting left bottom" << std::endl;
		    angle = (rand() % 35 + 30);
		    angle = angle;
		    }
		    return direction;
	}
    else if (ball.getGlobalBounds().intersects(rightPaddle.getGlobalBounds()))
	{
	    blip.play();
	    direction = -1;
	    if (ball.getPosition().y < rightPaddle.getPosition().y + 30)
		{
		    std::cout << "hitting the top right" << std::endl;
		    angle = (rand() % 35 + 30); 
		    angle = -angle;
		}
	    else if (ball.getPosition().y >  rightPaddle.getPosition().y + 30 && rightPaddle.getPosition().y < rightPaddle.getPosition().y + 50)
		{
		    std::cout << "right paddle middle" << std::endl;
		    angle = 0;
		}
	    else if (ball.getPosition().y > rightPaddle.getPosition().y + 50)
		{
		    std::cout << "hitting right bottom" << std::endl;
		    angle = (rand() % 35 + 30);
		    angle = angle;
		}
		    return direction;
	}
    else
	return direction;
}
void ai_paddle(sf::RectangleShape& ball, sf::RectangleShape& rightPaddle, int& direction, sf::Clock& clock, const int& gameHeight)
{
    float aiDistance = 40;
    float elapsed2 = clock.getElapsedTime().asSeconds();
    //cap ai speed
    if ( elapsed2 == 5.f)
	elapsed2 = 5.f;
    float aiSpeed = aiDistance/elapsed2;
    //Keep paddle  from going to far up
	    if ( rightPaddle.getPosition().y < ball.getPosition().y)
	      {
		    rightPaddle.move(0, aiSpeed);
		    if (rightPaddle.getPosition().y <= 0.f)
			{
			    rightPaddle.setPosition(760, 0);
			}
		}
	    //Keep paddle from going to far down
	    if (rightPaddle.getPosition().y  > ball.getPosition().y)
		{
		    rightPaddle.move(0, -aiSpeed);
		    if (rightPaddle.getPosition().y >= 500.f)
			{
			    rightPaddle.setPosition(760, 499);
			}
		}
	 
	    //  std::cout << rightPaddle.getPosition().y << std::endl;	
}
