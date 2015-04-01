#include <SFML/Graphics.hpp>

#include <thread>
#include <vector>
#include <iostream>

#include "Ship.h"
#include "Bullet.h"
#include "EnemyShip.h"
#include "Explosion.h"
#include "Utils.h"
#include "TextureManager.h"

int main()
{
  Utils::initPRNG();
  sf::RenderWindow window(sf::VideoMode(1280, 720), "Test");
  window.setFramerateLimit(60);

  // load textures
  TextureManager textureManager;
  textureManager.add("background1", "../../graphics/background1.png");
  textureManager.add("ownShip", "../../graphics/ownShip.png");
  textureManager.add("enemy1", "../../graphics/enemy1.png");
  textureManager.add("bullet", "../../graphics/bullet.png");
  textureManager.add("explosion", "../../graphics/explosion.png");
  
  // display kill counter
  int killCounter = 0;
  sf::Font font;
  if (!font.loadFromFile("../../font/unispace_bold.ttf")) {
    // logging...
    std::cout << "could not load font" << std::endl;
  }
  sf::Text killCounterText;
  killCounterText.setFont(font);
  killCounterText.setCharacterSize(50);
  killCounterText.setColor(sf::Color::White);
  killCounterText.setPosition(20, 20);
  killCounterText.setString(std::to_string(killCounter));

  // own ship
  Ship ownShip(362, 620, textureManager.get("ownShip"));

  // bullets, enemy ships and explosions
  std::vector<Bullet*> curBullets;
  std::vector<Bullet*>::iterator curBulletsIt;
  std::vector<EnemyShip*> curEnemyShips;
  std::vector<EnemyShip*>::iterator curEnemyShipsIt;
  std::vector<Explosion*> curExplosions;
  std::vector<Explosion*>::iterator curExplosionsIt;
  
  // background image
  sf::Sprite backgroundSprite(*(textureManager.get("background1")));
  float scaleX = 1280.0f/1920.0f;
  float scaleY = 720.0f/1080.0f;
  backgroundSprite.scale(scaleX, scaleY);

  // start clock
  sf::Clock clock;
  float tickLength;

  // game loop
  while (window.isOpen()) {
    tickLength = clock.restart().asSeconds();
    std::cout << int(tickLength * 250) << std::endl;

    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    window.clear();

    int newEnemyShip = Utils::getRandomNumber(1, 200);
    if (newEnemyShip == 1) {
      EnemyShip *e = new EnemyShip(Utils::getRandomNumber(10, 1235), 30, textureManager.get("enemy1"));
      curEnemyShips.push_back(e);
    }

    // draw background
    window.draw(backgroundSprite);
    // draw kill counter
    window.draw(killCounterText);
    // draw own ship
    window.draw(ownShip.animate(tickLength));

    // proccess bullets
    for (curBulletsIt = curBullets.begin();
         curBulletsIt != curBullets.end();) {      
      window.draw((*curBulletsIt)->animate(tickLength));
      if ((*curBulletsIt)->isProcessed()) {
        delete *curBulletsIt;
        curBulletsIt = curBullets.erase(curBulletsIt);
      } else {
        ++curBulletsIt;
      }
    }

    // process enemy ships
    for (curEnemyShipsIt = curEnemyShips.begin();
         curEnemyShipsIt != curEnemyShips.end();) {      
      window.draw((*curEnemyShipsIt)->animate(tickLength));
      if ((*curEnemyShipsIt)->isProcessed()) {
        delete *curEnemyShipsIt;
        curEnemyShipsIt = curEnemyShips.erase(curEnemyShipsIt);
      } else {
        ++curEnemyShipsIt;
      }
    }

    // process explosions
    for (curExplosionsIt = curExplosions.begin();
         curExplosionsIt != curExplosions.end();) {
      window.draw((*curExplosionsIt)->animate(tickLength));
      if ((*curExplosionsIt)->isProcessed()) {
        delete *curExplosionsIt;
        curExplosionsIt = curExplosions.erase(curExplosionsIt);
      } else {
        ++curExplosionsIt;
      }
    }

    // check collision between enemy and bullet
    for (curBulletsIt = curBullets.begin();
         curBulletsIt != curBullets.end();
         ++curBulletsIt) {
      for (curEnemyShipsIt = curEnemyShips.begin();
           curEnemyShipsIt != curEnemyShips.end();) {
        if ((*curBulletsIt)->intersects(*curEnemyShipsIt)) {
          Explosion *ex = new Explosion((*curEnemyShipsIt)->getPositionX(), (*curEnemyShipsIt)->getPositionY(), textureManager.get("explosion"));
          curExplosions.push_back(ex);
          delete *curEnemyShipsIt;
          curEnemyShipsIt = curEnemyShips.erase(curEnemyShipsIt);
          killCounter++;
          killCounterText.setString(std::to_string(killCounter));
        } else {
          ++curEnemyShipsIt;
        }
      }
    }

    // check collision between enemy and own ship
    for (curEnemyShipsIt = curEnemyShips.begin();
         curEnemyShipsIt != curEnemyShips.end();
         ++curEnemyShipsIt) {
      if (ownShip.intersects(*curEnemyShipsIt)) {
        window.close();
      }
    }

    window.display();

    // user input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      ownShip.move(sf::Keyboard::Left);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      ownShip.move(sf::Keyboard::Right);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
      int x = ownShip.getPositionX() + 32;
      int y = ownShip.getPositionY();
      Bullet *b = new Bullet(x, y, textureManager.get("bullet"));
      curBullets.push_back(b);
    }
  }

  return 0;
}
