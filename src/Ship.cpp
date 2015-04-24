#include "Ship.h"
#include <iostream>

Ship::Ship()
: GameObject(),
  lives(3),
  velocity(300) {}

Ship::Ship(int x, int y, sf::Texture *texture)
: GameObject(x, y, texture),
  lives(3),
  velocity(300),
  extraFire(false),
  isMovingUp(false),
  isMovingDown(false),
  isMovingLeft(false),
  isMovingRight(false),
  weightlessVelocityUp(0),
  weightlessVelocityDown(0),
  weightlessVelocityLeft(0),
  weightlessVelocityRight(0) {}

Ship::~Ship() {}

void Ship::move(float tickLength) {}

void Ship::move(float tickLength, bool isMovingUp, bool isMovingDown,
                bool isMovingLeft, bool isMovingRight) {
  if (isMovingUp) {
    // move up if key up was pressed
    if (this->position.y > 10) {
      this->position.y -= tickLength * this->velocity;
      this->weightlessVelocityUp = 0;
    }
  }
  if (isMovingDown) {
    // move down if key down was pressed
    if (this->position.y < 620) {
      this->position.y += tickLength * this->velocity;
      this->weightlessVelocityDown = 0;
    }
  }
  if (isMovingLeft) {
    // move left if key left was pressed
    if (this->position.x > 10) {
      this->position.x -= tickLength * this->velocity;
      this->weightlessVelocityLeft = 0;
    }
  }
  if (isMovingRight) {
    // move right if key right was pressed
    if (this->position.x < 1235) {
      this->position.x += tickLength * this->velocity;
      this->weightlessVelocityRight = 0;
    }
  }

  // weightless movement
  if (this->position.y > 10) {
    this->position.y -= tickLength * this->weightlessVelocityUp;
  }
  if (this->position.y < 620) {
    this->position.y += tickLength * this->weightlessVelocityDown;
  }
  if (this->position.x > 10) {
    this->position.x -= tickLength * this->weightlessVelocityLeft;
  }
  if (this->position.x < 1235) {
    this->position.x += tickLength * this->weightlessVelocityRight;
  }


  if (isMovingUp == false && this->isMovingUp != isMovingUp && this->weightlessVelocityUp == 0) {
    this->weightlessVelocityUp = 300;
  }
  if (this->weightlessVelocityUp > 0) {
    this->weightlessVelocityUp -= 10;
  }
  this->isMovingUp = isMovingUp;

  if (isMovingDown == false && this->isMovingDown != isMovingDown && this->weightlessVelocityDown == 0) {
    this->weightlessVelocityDown = 300;
  }
  if (this->weightlessVelocityDown > 0) {
    this->weightlessVelocityDown -= 10;
  }
  this->isMovingDown = isMovingDown;

  if (isMovingLeft == false && this->isMovingLeft != isMovingLeft && this->weightlessVelocityLeft == 0) {
    this->weightlessVelocityLeft = 300;
  }
  if (this->weightlessVelocityLeft > 0) {
    this->weightlessVelocityLeft -= 10;
  }
  this->isMovingLeft = isMovingLeft;

  if (isMovingRight == false && this->isMovingRight != isMovingRight && this->weightlessVelocityRight == 0) {
    this->weightlessVelocityRight = 300;
  }
  if (this->weightlessVelocityRight > 0) {
    this->weightlessVelocityRight -= 10;
  }
  this->isMovingRight = isMovingRight;

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

bool Ship::getExtraFire() {
  return this->extraFire;
}

void Ship::setExtraFire(bool extraFire) {
  this->extraFire = extraFire;
}