#include "EnemyShip.h"

EnemyShip::EnemyShip()
: GameObject() {
  this->type = "EnemyShip";
}

EnemyShip::EnemyShip(int x, int y, sf::Texture *texture)
: GameObject(x, y, texture) {
  this->type = "EnemyShip";
}

EnemyShip::~EnemyShip() {}

void EnemyShip::move(float tickLength) {
  this->position.y += tickLength * 200;
  this->sprite->setPosition(position);
  if (this->position.y > 600) {
    this->processed = true;
  }
}
