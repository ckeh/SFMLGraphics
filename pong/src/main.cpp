#include <SFML/Graphics.hpp>
#include <iostream>
#include "ball.cpp"

int main()
{
  sf::RenderWindow window(sf::VideoMode(800,600), "MyGame!");
	window.setFramerateLimit(60);
	window.requestFocus();
  Ball ball;
	while (window.isOpen()){
    sf::Event event;
    while (window.pollEvent(event)){
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        ball.bmotion.up = 1;
        ball.move(0,-ball.getVel());	
      }
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        ball.move(0,ball.getVel());	
      }
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        ball.move(-ball.getVel(),0);	
      }
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        ball.move(ball.getVel(),0);	
      }
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
        ball.decreVel();	
      }
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
        ball.incrVel();	
      }
      if (event.type == sf::Event::Closed)
        window.close();
    }
    window.clear();
		ball.update(&window, );
    window.display();
  }

return 0;
}
