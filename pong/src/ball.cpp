#include <SFML/Graphics.hpp>
#include "enum.hpp"

class Ball{
	private:
		Motion bmotion;	
    sf::CircleShape* ball;
	public:
		Ball(){
			ball = new sf::CircleShape(10.f);
      ball->setFillColor(sf::Color::Green);
			bmotion.vel = 1;
			bmotion.up = 0;
			bmotion.down = 0;
			bmotion.left = 0;
			bmotion.right = 0;
		}
		void incrVel(){
			vel++;
		}
		void decreVel(){
			vel--;
		}
		float getVel(){
			return vel; 
		}
		void move(float x,float y){
			ball->move(x,y);
		}
		void drawBall(sf::RenderWindow* window){
			window->draw(*ball);
		}
		void updateBall(sf::RenderWindow* window){
			
		}
};
