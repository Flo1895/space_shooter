#ifndef SHIP_H_
#define SHIP_H_

#include <string>

#include "GameObject.h"

#include <SFML/Graphics.hpp>

class Ship : public GameObject {
private:
  int lives;
  int velocity;

public:
  Ship();
  Ship(int x, int y, sf::Texture *texture);
  ~Ship();
  void move(float tickLength);
  void move(float tickLength, bool isMovingUp, bool isMovingDown,
  	        bool isMovingLeft, bool isMovingRight);
  int getLives();
  void decreaseLives();
  void resetLives();
};

#endif // SHIP_H_
