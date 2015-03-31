#include "EnemyShip.h"

EnemyShip::EnemyShip()
: GameObject() {}

EnemyShip::EnemyShip(int x, int y, std::string texturePath)
: GameObject(x, y, texturePath) {}

EnemyShip::~EnemyShip() {}

sf::Sprite EnemyShip::animate() {
  this->position.y += 2;
  this->sprite->setPosition(position);
  if (this->position.y > 600) {
    this->processed = true;
  }
  return *(this->sprite);
}
