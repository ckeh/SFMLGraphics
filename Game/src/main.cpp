#include <SFML/Graphics.hpp>
#include <iostream>
#include "ball.cpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600), "MyGame!");
	window.setFramerateLimit(60);
	window.requestFocus();
    Ball ball;
	while (window.isOpen())
    {
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
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
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
		ball.drawBall(&window);
        window.display();
    }

    return 0;
}
