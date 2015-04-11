#include "Bullet.h"

Bullet::Bullet()
: GameObject() {
  this->type = "Bullet";
}

Bullet::Bullet(int x, int y, sf::Texture *texture)
: GameObject(x, y, texture) {
  this->type = "Bullet";
}

Bullet::~Bullet() {}

void Bullet::move(float tickLength) {
  this->position.y -= tickLength*250;
  this->sprite->setPosition(position);
  if (this->position.y < 0) {
    this->processed = true;
  }
}
