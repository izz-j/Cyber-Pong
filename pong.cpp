//Authors: Iseman Johnson
//First Pong game
#include <iostream>
#include <math.h>//for sine and cosine
#include <stdlib.h> //for srand and rand
#include <SFML/Graphics.hpp>//for graphics
#include <SFML/Audio.hpp> //for sound

  float pi = 3.1415;
void ball_traits(sf::RectangleShape& ball, sf::RectangleShape& leftPaddle, sf::RectangleShape& rightPaddle, int& direction, sf::Clock& clock, float& angle, sf::Sound& wallSound, int& scoreLeft, int& scoreRight, std::string& left, std::string& right, sf::Text& textLeft, sf::Text& textRight);
int paddle_collision(const int& paddleSizeY, sf::RectangleShape& ball, sf::RectangleShape& leftPaddle, sf::RectangleShape& rightPaddle, int& direction, float& angle, sf::Sound& paddleSound);
void ai_paddle(sf::RectangleShape& ball, sf::RectangleShape& rightPaddle,  int& direction, sf::Clock& clock, const int& gameHeight);

int main()
{
int direction = -1;
 sf::Clock clock;
  const int gameWidth = 800;
  const int gameHeight = 600;
  std::srand(time(0));
  // initialized with 00 as a placeholder
  std::string left = "00";
  std::string right = "00";
  int scoreLeft = 0;
  int scoreRight = 0;
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
    //Create the line down the middle
    sf::RectangleShape line(sf::Vector2f(4, 600));
    line.setFillColor(sf::Color::White);
    line.setPosition(399, 0);
    //ball initial angle
     float angle = 0;
     //load sound
     sf::SoundBuffer blipBuffer;
     sf::SoundBuffer blip2Buffer;
     if (!blipBuffer.loadFromFile("audio/pongblip.wav"))
        return -1;
     if (!blip2Buffer.loadFromFile("audio/wallsound.wav"))
	 return -1;
     sf::Sound paddleSound;
     sf::Sound wallSound;
     paddleSound.setBuffer(blipBuffer);
     wallSound.setBuffer(blip2Buffer);

    //Load font
    sf::Font font;
    if(!font.loadFromFile("fonts/half_bold_pixel-7.ttf"))
        return -1;
    //creating text objects and giving them parameters
    sf::Text textLeft;
    sf::Text textRight;
    textLeft.setFont(font);
    textRight.setFont(font);

    textLeft.setString((left[1]));
    textRight.setString((right[1]));

    textLeft.setCharacterSize(100);
    textRight.setCharacterSize(100);

    textLeft.setColor(sf::Color::Red);
    textRight.setColor(sf::Color::Red);

    textLeft.setPosition(200, 200);
    textRight.setPosition(570, 200);

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
	ball_traits(ball, leftPaddle, rightPaddle, direction, clock, angle, wallSound, scoreLeft, scoreRight, left, right, textLeft, textRight);
	//Paddle collisions
	paddle_collision(paddleSizeY, ball, leftPaddle, rightPaddle, direction, angle, paddleSound);
	//AI
	ai_paddle(ball, rightPaddle,  direction, clock, gameHeight);
	//std::cout << ball.getPosition().y << std::endl;
	//clear
        window.clear();
	//draw
        window.draw(leftPaddle);
	window.draw(rightPaddle);
	window.draw(textLeft);
	window.draw(textRight);
	window.draw(line);
	window.draw(ball);
        window.display();
    }

    return 0;
}
void ball_traits(sf::RectangleShape& ball, sf::RectangleShape& leftPaddle, sf::RectangleShape& rightPaddle, int& direction, sf::Clock& clock, float& angle, sf::Sound& wallSound, int& scoreLeft, int& scoreRight, std::string& left, std::string& right, sf::Text& textLeft, sf::Text& textRight)
{
  //So my error was I had to add asSeconds() to make the ball go faster

  //temp is used for integer to character conversions
  char temp;
  float elapsed= clock.getElapsedTime().asSeconds();
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
      wallSound.play();
      angle = -angle;
      ball.move(moveX, -moveY * elapsed);
  }
  else if (ball.getPosition().y > 578.f)
	{
	    wallSound.play();
	    angle = -angle;
	    ball.move(moveX, -moveY * elapsed);
	}
  
  
  //prevent the ball from going out of  bounds passed the paddle
  if (ball.getPosition().x < leftPaddle.getPosition().x || ball.getPosition().x > rightPaddle.getPosition().x)
  {
      //increment scores based on which side the ball went to
      if(ball.getPosition().x < leftPaddle.getPosition().x)
      {
	  scoreRight++;
      }
      else if(ball.getPosition().x > rightPaddle.getPosition().x)
      {
	  scoreLeft++;
      }
      
      if(scoreLeft > 9)
      {
	  //get the tens digit and convert to character
	  temp = scoreLeft/10 + '0';
	  left[0] = temp;
	  //get the ones digit and convert to character
	  temp = scoreLeft%10 + '0';
	  left[1] = temp;
      }
      else if(scoreLeft < 10)
      {
	  //get the digit and convert to character
	  temp = scoreLeft + '0';
	  left[0] = '0';
	  left[1] = temp;
      }
      //comments for scoreLeft above apply below for scoreRight
      if(scoreRight > 9)
      {
	  temp = scoreRight/10 + '0';
	  right[0] = temp;
	  temp = scoreRight%10 + '0';
	  right[1] = temp;
      }
      else if(scoreRight < 10)
      {
	  temp = scoreRight + '0';
	  right[0] = '0';
            right[1] = temp;
      }
      //if the tens digit is 0, that means the score is less than 10, so only the ones digit is used
      if(left[0] == '0')
      {
	  textLeft.setString(left[1]);
      }
      //otherwise both digits are used
      else
      {
	  textLeft.setString((left));
      }
      //repeat comments for right
      if(right[0] == '0')
      {
            textRight.setString(right[1]);
      }
      else
      {
	  textRight.setString((right));
      }
      //reset everything
      ball.setPosition(250, 200);
        leftPaddle.setPosition(20, 200);
        rightPaddle.setPosition(760,  200);
        angle = 0;
        direction *= -1;
        clock.restart();
	
  }
  
}

int paddle_collision(const int& paddleSizeY, sf::RectangleShape& ball, sf::RectangleShape& leftPaddle, sf::RectangleShape& rightPaddle, int& direction, float& angle, sf::Sound& paddleSound)
{
    if (ball.getGlobalBounds().intersects(leftPaddle.getGlobalBounds()))
    {
	paddleSound.play();
	direction = 1;
	    //std::cout << ball.getPosition().y << std::endl;
	if (ball.getPosition().y < leftPaddle.getPosition().y + 30)
	{
	    //std::cout << "Hitting the top left" << std::endl;
	    angle = (rand() % 35 + 30);
	    angle = -angle;
	}
	else if (ball.getPosition().y >  leftPaddle.getPosition().y + 30 && ball.getPosition().y < leftPaddle.getPosition().y + 50)
	{
	    //std::cout << "hitting left middle" << std::endl;
	    angle = 0;
	}
	else if (ball.getPosition().y >  leftPaddle.getPosition().y  + 50)
	{
	    //std::cout << "hitting left bottom" << std::endl;
	    angle = (rand() % 35 + 30);
	    angle = angle;
	}
	return direction;
    }
    else if (ball.getGlobalBounds().intersects(rightPaddle.getGlobalBounds()))
    {
	paddleSound.play();
	    direction = -1;
	    if (ball.getPosition().y < rightPaddle.getPosition().y + 30)
	    {
		//std::cout << "hitting the top right" << std::endl;
		angle = (rand() % 35 + 30);
		angle = -angle;
	    }
	    else if (ball.getPosition().y >  rightPaddle.getPosition().y + 30 && ball.getPosition().y < rightPaddle.getPosition().y + 50)
	    {
		//std::cout << "right paddle middle" << std::endl;
		angle = 0;
	    }
	    else if (ball.getPosition().y > rightPaddle.getPosition().y + 50)
		{
		    //std::cout << "hitting right bottom" << std::endl;
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
    if (ball.getPosition().y < rightPaddle.getPosition().y)
    {
	if (rightPaddle.getPosition().y <= 0.f)
	{
	    rightPaddle.setPosition(760, 0);
	}
	else
	rightPaddle.move(0, -aiSpeed);
	
    }
	    //Keep paddle from going to far down
    if (ball.getPosition().y > rightPaddle.getPosition().y)
    {
	if (rightPaddle.getPosition().y > gameHeight - 100)
	{
	    rightPaddle.setPosition(760, 500);
	}
	else 
	    rightPaddle.move(0, aiSpeed);
    }

    // std::cout << rightPaddle.getPosition().y << std::endl;
}
