#include "Ship.h"

Ship::Ship()
: GameObject() {}

Ship::Ship(int x, int y, sf::Texture *texture)
: GameObject(x, y, texture) {}

Ship::~Ship() {}

void Ship::move(float tickLength) {}

void Ship::move(float tickLength, bool isMovingLeft, bool isMovingRight) {
  if (isMovingLeft) {
    // move left if key left was pressed
    if (this->position.x > 10) {
      this->position.x -= tickLength*300.0f;
      this->sprite->setPosition(this->position);
    }
  }
  else if (isMovingRight) {
    // move right if key right was pressed
    if (this->position.x < 1235) {
      this->position.x += tickLength*300.0f;
      this->sprite->setPosition(this->position);
    }
  }
}