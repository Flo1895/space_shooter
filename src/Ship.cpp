#include "Ship.h"

Ship::Ship()
: GameObject(),
  lives(3),
  velocity(300) {}

Ship::Ship(int x, int y, sf::Texture *texture)
: GameObject(x, y, texture),
  lives(3),
  velocity(300) {}

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

int Ship::getLives() {
  return this->lives;
}

void Ship::decreaseLives() {
  this->lives--;
}

void Ship::resetLives() {
  this->lives = 3;
}