#include <SFML/Graphics.hpp>
#include <iostream>
#include "line.cpp"

#define MENU 0
#define GAME 1
#define GAMEOVER 2

int main(){
	sf::RenderWindow window(sf::VideoMode(WINDOW_X,WINDOW_Y), "MyGame!");
	window.setFramerateLimit(144);
	window.requestFocus();
	allPlatforms* ap; 
	ap = new allPlatforms();
	Player p;
	Motion m;
	Spikes s;
	int GAME_MODE = MENU;
	sf::Font font;
	if (!font.loadFromFile("font.ttf")) return -1;
	int count =0;
	sf::Text score("Score:" + std::to_string(count),font);
	score.setCharacterSize(50); // in pixels, not points!
	score.setFillColor(sf::Color::Green);
    sf::Event event;
	while (window.isOpen()){
        window.clear();
		switch (GAME_MODE){
			case MENU:{
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                    sf::Text score("Score:" + std::to_string(count),font);
					GAME_MODE = GAME;
				}
			break;}
			case GAME:{
			while (window.pollEvent(event)){
				if (event.type == sf::Event::Closed){
					window.close();
				}
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
				}
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
				}
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
					m.left = 1;
				}
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
					m.right = 1;
				}
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) | sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
					m.xVel = 3;
				}
				if(event.type == sf::Event::KeyReleased){
					if( event.key.code == sf::Keyboard::LShift | event.key.code == sf::Keyboard::RShift){
						m.xVel = 2;
					}
					if(event.key.code == sf::Keyboard::Left){
						m.left = 0;
					}
					if(event.key.code == sf::Keyboard::Right){
						m.right = 0;
					}
				}
			}
			Motion pMove = p.getMotion();
			if(p.getPos().x <11 |p.getPos().x+PLAYER_SIZE >WINDOW_X - 11|p.getPos().y<11 | p.getPos().y>WINDOW_Y-11){
				GAME_MODE = GAMEOVER;
			} else if(ap->inHole(&p)){
				m.inhole = 1;
				m.down = 1;
				m.up = 0;
				m.yVel = 2;
			} else if(ap->collisionCheck(&p)){
				m.yVel = ap->getAllSpeed();	
			} else {
				if(m.inhole == 1){
					count++;
					score.setString("Score:" + std::to_string(count));
				}
				m.down = 1;
				m.up = 0;
				m.yVel = 2;
				m.inhole = 0;
			}
			ap->updateAllPlat(&window);
			p.updatePlayer(&window, m);
			s.drawSpike(&window);
			window.draw(score);
			break;
			}
			case GAMEOVER:{
                sf::Text gameover("Game Over\nYour Final Score Was "+std::to_string(count)+"\nHit Spacebar to Continue...",font); 
                gameover.setCharacterSize(50); // in pixels, not points!
                gameover.setFillColor(sf::Color::Green);
			    window.draw(gameover);
				delete ap;
				ap = new allPlatforms();
				p.reset();
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                    count = 0;
					GAME_MODE = MENU;
				}

			break;
			}
		}
        window.display();
	}
}

