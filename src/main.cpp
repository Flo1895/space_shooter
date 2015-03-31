#include <SFML/Graphics.hpp>

#include <thread>
#include <vector>
#include <iostream>

#include "Ship.h"
#include "Bullet.h"
#include "EnemyShip.h"
#include "Utils.h"

int main()
{
  Utils::initPRNG();
  sf::RenderWindow window(sf::VideoMode(800, 600), "Test");
  
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

  Ship ownShip(362, 500, "../../graphics/ownShip.png");
  std::vector<Bullet*> curBullets;
  std::vector<Bullet*>::iterator curBulletsIt;
  std::vector<EnemyShip*> curEnemyShips;
  std::vector<EnemyShip*>::iterator curEnemyShipsIt;
  EnemyShip *e = new EnemyShip(362, 30, "../../graphics/enemy1.png");
  curEnemyShips.push_back(e);

  sf::Texture backgroundTexture;
  if (!backgroundTexture.loadFromFile("../../graphics/background.png")) {
    return EXIT_FAILURE;
  }
  backgroundTexture.setSmooth(true);
  backgroundTexture.setRepeated(true);
  sf::Sprite backgroundSprite(backgroundTexture);
  backgroundSprite.setTextureRect(sf::IntRect(0, 0, 800, 600));

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    window.clear();

    int newEnemyShip = Utils::getRandomNumber(1, 200);
    if (newEnemyShip == 1) {
      EnemyShip *e = new EnemyShip(Utils::getRandomNumber(10, 590), 30, "../../graphics/enemy1.png");
      curEnemyShips.push_back(e);
    }

    window.draw(backgroundSprite);
    // display kill counter
    window.draw(killCounterText);
    window.draw(ownShip.animate());
    // proccess bullets
    for (curBulletsIt = curBullets.begin();
         curBulletsIt != curBullets.end();) {      
      window.draw((*curBulletsIt)->animate());
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
      window.draw((*curEnemyShipsIt)->animate());
      if ((*curEnemyShipsIt)->isProcessed()) {
        delete *curEnemyShipsIt;
        curEnemyShipsIt = curEnemyShips.erase(curEnemyShipsIt);
      } else {
        ++curEnemyShipsIt;
      }
    }
    // check collision between enemy and bullet
    for (curBulletsIt = curBullets.begin();
         curBulletsIt != curBullets.end();
         ++curBulletsIt) {
      for (curEnemyShipsIt = curEnemyShips.begin();
           curEnemyShipsIt != curEnemyShips.end();) {
        if ((*curBulletsIt)->intersects(*curEnemyShipsIt)) {
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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      ownShip.move(sf::Keyboard::Left);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      ownShip.move(sf::Keyboard::Right);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
      int x = ownShip.getPositionX() + 32;
      int y = ownShip.getPositionY();
      Bullet *b = new Bullet(x, y, "../../graphics/bullet.png");
      curBullets.push_back(b);
    }
  }

  return 0;
}
