#ifndef SHIP_H_
#define SHIP_H_

#include <string>

#include "GameObject.h"

#include <SFML/Graphics.hpp>

class Ship : public GameObject {
public:
  Ship();
  Ship(int x, int y, std::string texturePath);
  ~Ship();
  void move(sf::Keyboard::Key key);
  sf::Sprite animate();
};

#endif // SHIP_H_
