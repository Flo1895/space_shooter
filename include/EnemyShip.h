#ifndef ENEMY_SHIP_H_
#define ENEMY_SHIP_H_

#include <string>

#include "GameObject.h"

#include <SFML/Graphics.hpp>

class EnemyShip : public GameObject {
public:
  EnemyShip();
  EnemyShip(int x, int y, std::string texturePath);
  ~EnemyShip();
  sf::Sprite animate();
};

#endif // ENEMY_SHIP_H_
