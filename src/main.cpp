#include <SFML/Graphics.hpp>

#include <thread>
#include <vector>

#include "Ship.h"
#include "Bullet.h"
#include "EnemyShip.h"

int main()
{
  sf::RenderWindow window(sf::VideoMode(800, 600), "Test");

  Ship ownShip(362, 500, "../../graphics/ownShip.png");
  std::vector<GameObject*> curGameObjects;
  std::vector<GameObject*>::iterator curGameObjectsIt;
  EnemyShip *e = new EnemyShip(362, 30, "../../graphics/enemy1.png");
  curGameObjects.push_back(e);

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
    window.draw(backgroundSprite);
    window.draw(ownShip.animate());
    for (curGameObjectsIt = curGameObjects.begin();
         curGameObjectsIt != curGameObjects.end();) {      
      window.draw((*curGameObjectsIt)->animate());
      if ((*curGameObjectsIt)->isProcessed()) {
        delete *curGameObjectsIt;
        curGameObjectsIt = curGameObjects.erase(curGameObjectsIt);
      } else {
        ++curGameObjectsIt;
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
      curGameObjects.push_back(b);
    }
  }

  return 0;
}
