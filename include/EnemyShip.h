#ifndef ENEMY_SHIP_H_
#define ENEMY_SHIP_H_

#include <string>

#include "GameObject.h"

#include <SFML/Graphics.hpp>

class EnemyShip : public GameObject {
private:
  float fireBackoff;

public:
  EnemyShip();
  EnemyShip(int x, int y, sf::Texture *texture);
  ~EnemyShip();
  void move(float tickLength);
  float getFireBackoff();
  void reduceFireBackoff(float timePerFrame);
  void resetFireBackoff();
};

#endif // ENEMY_SHIP_H_
