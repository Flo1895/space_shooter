#include "EnemyShip.h"

EnemyShip::EnemyShip()
: GameObject() {}

EnemyShip::EnemyShip(int x, int y, sf::Texture *texture)
: GameObject(x, y, texture), moveYPerSecond(250) {}

EnemyShip::~EnemyShip() {}

sf::Sprite EnemyShip::animate(float tickLength) {
  this->position.y += int(tickLength * this->moveYPerSecond);
  this->sprite->setPosition(position);
  if (this->position.y > 600) {
    this->processed = true;
  }
  return *(this->sprite);
}
