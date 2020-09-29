#include <SFML/Graphics.hpp>
#include <iostream>
#include "line.cpp"

#define MENU 0
#define GAME 1
#define GAMEOVER 2

int main()
{
  sf::RenderWindow window(sf::VideoMode(WINDOW_X,WINDOW_Y), "MyGame!");
	window.setFramerateLimit(144);
	window.requestFocus();
	allPlatforms ap;
	Player p;
	Motion m;
	Spikes s;
  std::string score;
  sf::Font font;
  if (!font.loadFromFile("/System/Library/Fonts/Menlo.ttc")) return -1;
  int count =0;
  score = "Score:" + std::to_string(count);
  sf::Text text(score,font);
  text.setCharacterSize(50); // in pixels, not points!
  text.setFillColor(sf::Color::Green);
  while (window.isOpen()){
    sf::Event event;
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
		if(ap.inHole(&p)){
      m.inhole = 1;
			m.down = 1;
			m.up = 0;
			m.yVel = 2;
		} else if(ap.collisionCheck(&p)){
			m.yVel = ap.getAllSpeed();	
		} else {
      if(m.inhole == 1){
        count++;
        score = "Score:" + std::to_string(count);
        text.setString(score);
      }
			m.down = 1;
			m.up = 0;
			m.yVel = 2;
      m.inhole = 0;
		}
    window.clear();
		s.drawSpike(&window);
		ap.updateAllPlat(&window);
		p.updatePlayer(&window, m);
    window.draw(text);
    window.display();
  }
}

