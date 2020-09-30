#include <SFML/Graphics.hpp>
#include <stdlib.h>

#define PLAYER_SIZE 50
#define PLAT_HEIGHT 50
#define NUM_PLAT 3
#define WINDOW_Y 600
#define WINDOW_X 800
#define SPACING WINDOW_Y-(WINDOW_Y/NUM_PLAT)

typedef struct {
	float x1;
	float x2;
	float size;
} Hole;

typedef struct motion{
	float xVel = 2;
	float yVel = 2;
	bool up = 0;
	bool down = 1;
	bool left = 0;
	bool right = 0;
	bool inhole = 0;
} Motion;

class Player{
	private:
		Motion pMove;
		sf::RectangleShape* player;
		void setMotion(Motion motion){
			pMove = motion;
			if(!pMove.inhole){
				if(pMove.left){
					player->move(-pMove.xVel,0.f);
				}
				if(pMove.right){
					player->move(pMove.xVel,0.f);
				}
			}
			if(pMove.down){
				player->move(0.f,pMove.yVel);
			}
			if(pMove.up){
				player->move(0.f,-pMove.yVel);
			}
		}
	public:
		Player(){
			player = new sf::RectangleShape(sf::Vector2f(PLAYER_SIZE,PLAYER_SIZE));
			player->setFillColor(sf::Color::Blue);
			player->setPosition(WINDOW_X/2,WINDOW_Y/2);
		}
		void updatePlayer(sf::RenderWindow* window, Motion motion){
			setMotion(motion);
			window->draw(*player);
		}
		sf::Vector2f getPos(){
			return player->getPosition();
		}
		void setPos(float x, float y){
			player->setPosition(x,y);
		}
		Motion getMotion(){
			return pMove;
		}
		sf::FloatRect getPlayerBounds(){
			return player->getGlobalBounds();
		}
		void reset(){
			player->setPosition(WINDOW_X/2,WINDOW_Y/2);
		}

};


class Spikes{
	private:
		sf::RectangleShape* spike;
	public:
		Spikes(){
			spike = new sf::RectangleShape(sf::Vector2f(30.0,30.0));
			spike->setFillColor(sf::Color::Red);
			spike->setPosition(0.0,0.0);
			spike->setRotation(45.0);
		}
		void drawSpike(sf::RenderWindow* window){
			for(int i = 0; i<WINDOW_Y; i+=50){
				for(int j = 0; j<WINDOW_X; j+=50){
					spike->setPosition(j+21.21,0.0-21.21);
					window->draw(*spike);
					spike->setPosition(j,WINDOW_Y-21.21);
					window->draw(*spike);
				}
				spike->setPosition(0.0,i);
				window->draw(*spike);
				spike->setPosition(WINDOW_X,i);
				window->draw(*spike);
			}
		}
};
/*
class AllSpikes{
	private:
		Spikes s[NUM_PLAT];
	public:
		void updateAllPlat(sf::RenderWindow* window){
    }
		bool collisionCheck(Player* ppos){
			bool ret = 0;
			sf::FloatRect pbound, platbound;
			pbound = ppos->getPlayerBounds();
			for(int i = 0; i<NUM_PLAT; i++){
				platbound = p[i].getPlatBounds();
				if(pbound.intersects(platbound)){
					ppos->setPos(pbound.left,p[i].getPos().y-PLAYER_SIZE-1);
					ret = 1;
				}
			}
			return ret;
		}
};
*/
class Platform{
	private:
    float speed;
		Hole holed;
		bool start;
		sf::RectangleShape* plat;
		sf::RectangleShape* hole;
		void resetPlat(){
			holed.x1 = rand()%(WINDOW_X-(int)holed.size-2*11)+11;
			holed.x2 = holed.x1+holed.size;
			plat->setSize(sf::Vector2f(WINDOW_X,PLAT_HEIGHT));
			hole->setSize(sf::Vector2f(holed.size,PLAT_HEIGHT));
			plat->setPosition(0.f,WINDOW_Y);
			hole->setPosition(holed.x1,WINDOW_Y);
		}
		bool hitTop(){
			if(plat->getPosition().y==0||hole->getPosition().y==0)
				return true;
			return false;
		}
	public:
		Platform(){
			start = 0;
			holed.size = 50;
			plat = new sf::RectangleShape(sf::Vector2f(WINDOW_X,PLAT_HEIGHT));
			hole = new sf::RectangleShape(sf::Vector2f(holed.x1,PLAT_HEIGHT));
			resetPlat();
			plat->setFillColor(sf::Color::Red);
			hole->setFillColor(sf::Color::Black);
			speed = 1;
		}
		~Platform(){
			delete plat;
			delete hole;
		}
		void updatePlat(sf::RenderWindow* window){
			if(start){
				window->draw(*plat);
				window->draw(*hole);
				plat->move(0.f,-speed);
				hole->move(0.f,-speed);
				if(hitTop()){
					resetPlat();
				}
			}
		}

		sf::Vector2f getPos(){
			return plat->getPosition();
		}
		sf::FloatRect getHole(){
			return hole->getGlobalBounds();
		}
		float getSpeed(){
			return speed;
		}
		void startPlat(){
			start = 1;
		}
		sf::FloatRect getPlatBounds(){
			return plat->getGlobalBounds();
		}
};

class allPlatforms{
	private:
		Platform p[NUM_PLAT];
		bool doneStarting;
	public:
		allPlatforms(){
			doneStarting = 0;
		}
		void updateAllPlat(sf::RenderWindow* window){
			p[0].startPlat();
			for(int i = 0; i<NUM_PLAT; i++){
				p[i].updatePlat(window);
				if(p[i].getPos().y == SPACING & !doneStarting){
					p[i+1].startPlat();
					if (i+1 == NUM_PLAT-1)
						doneStarting = true;
				}
			}
		}
		bool collisionCheck(Player* ppos){
			bool ret = 0;
			sf::FloatRect pbound, platbound;
			pbound = ppos->getPlayerBounds();
			for(int i = 0; i<NUM_PLAT; i++){
				platbound = p[i].getPlatBounds();
				if(pbound.intersects(platbound)){
					ppos->setPos(pbound.left,p[i].getPos().y-PLAYER_SIZE-1);
					ret = 1;
				}
			}
			return ret;
		}
		bool inHole(Player* ppos){
			bool ret = 0;
			sf::FloatRect pbound, hbound;
			pbound = ppos->getPlayerBounds();
			for(int i = 0; i<NUM_PLAT; i++){
				hbound = p[i].getHole();
				if((pbound.left>=hbound.left-1 && pbound.left+pbound.width <= hbound.left+hbound.width+1)&&pbound.intersects(hbound)){
					ppos->setPos(hbound.left,pbound.top);
					ret = 1;
				}
			}
			return ret;
		}
		float getAllSpeed(){
			return p[0].getSpeed();
		}
};

