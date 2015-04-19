#include "LivePowerUp.h"

LivePowerUp::LivePowerUp()
: GameObject(), velocity(150) {
  this->type = "LivePowerUp";
}

LivePowerUp::LivePowerUp(int x, int y, sf::Texture *texture)
: GameObject(x, y, texture), velocity(150) {
  this->type = "LivePowerUp";
}

LivePowerUp::~LivePowerUp() {}

void LivePowerUp::move(float tickLength) {
  this->position.y += tickLength * this->velocity;
  this->sprite->setPosition(position);
  if (this->position.y > 600) {
    this->processed = true;
  }
}