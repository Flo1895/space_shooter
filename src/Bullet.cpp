#include "Bullet.h"

Bullet::Bullet()
: GameObject() {
  this->type = "Bullet";
}

Bullet::Bullet(int x, int y, sf::Texture *texture, Direction direction)
: GameObject(x, y, texture) {
  this->type = "Bullet";
  this->direction = direction;
}

Bullet::~Bullet() {}

void Bullet::move(float tickLength) {
  if (this->direction == UP) {
    this->position.y -= tickLength*250;
  } else {
  	this->position.y += tickLength*250;
  }
  this->sprite->setPosition(position);
  if (this->position.y < 0) {
    this->processed = true;
  }
}
