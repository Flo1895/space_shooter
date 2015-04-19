#include "Ship.h"

Ship::Ship()
: GameObject(), velocity(300) {}

Ship::Ship(int x, int y, sf::Texture *texture)
: GameObject(x, y, texture), velocity(300) {}

Ship::~Ship() {}

void Ship::move(float tickLength) {}

void Ship::move(float tickLength, bool isMovingUp, bool isMovingDown,
                bool isMovingLeft, bool isMovingRight) {
  if (isMovingUp) {
    // move up if key up was pressed
    if (this->position.y > 10) {
      this->position.y -= tickLength * this->velocity;
    }
  }
  if (isMovingDown) {
    // move down if key down was pressed
    if (this->position.y < 620) {
      this->position.y += tickLength * this->velocity;
    }
  }
  if (isMovingLeft) {
    // move left if key left was pressed
    if (this->position.x > 10) {
      this->position.x -= tickLength * this->velocity;
    }
  }
  if (isMovingRight) {
    // move right if key right was pressed
    if (this->position.x < 1235) {
      this->position.x += tickLength * this->velocity;
    }
  }

  this->sprite->setPosition(this->position);
}