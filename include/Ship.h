#ifndef SHIP_H_
#define SHIP_H_

#include <string>

#include "GameObject.h"

#include <SFML/Graphics.hpp>

class Ship : public GameObject {
public:
  Ship();
  Ship(int x, int y, sf::Texture *texture);
  ~Ship();
  void move(float tickLength);
  void move(float tickLength, bool isMovingLeft, bool isMovingRight);
};

#endif // SHIP_H_
