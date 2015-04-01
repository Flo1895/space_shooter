#ifndef ENEMY_SHIP_H_
#define ENEMY_SHIP_H_

#include <string>

#include "GameObject.h"

#include <SFML/Graphics.hpp>

class EnemyShip : public GameObject {
private:
  int moveYPerSecond;

public:
  EnemyShip();
  EnemyShip(int x, int y, sf::Texture *texture);
  ~EnemyShip();
  sf::Sprite animate(float tickLength);
};

#endif // ENEMY_SHIP_H_
