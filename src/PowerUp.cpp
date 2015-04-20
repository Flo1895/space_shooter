#include "PowerUp.h"

PowerUp::PowerUp()
: GameObject(),
  velocity(150) {
  this->type = "PowerUp";
}

PowerUp::PowerUp(int x, int y, std::string type, sf::Texture *texture)
: GameObject(x, y, texture),
  velocity(150) {
  this->type = type;
}

PowerUp::~PowerUp() {}

void PowerUp::move(float tickLength) {
  this->position.y += tickLength * this->velocity;
  this->sprite->setPosition(position);
  if (this->position.y > 600) {
    this->processed = true;
  }
}