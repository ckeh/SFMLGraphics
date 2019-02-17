#include <SFML/Graphics.hpp>

class Ball{
	private:
		float vel; 
    	sf::CircleShape* ball;
	public:
		Ball(){
			ball = new sf::CircleShape(10.f);
    		ball->setFillColor(sf::Color::Green);
			vel = 1;
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
};
