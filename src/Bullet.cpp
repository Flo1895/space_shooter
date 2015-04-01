#include "Bullet.h"

Bullet::Bullet()
: GameObject() {}

Bullet::Bullet(int x, int y, sf::Texture *texture)
: GameObject(x, y, texture) {}

Bullet::~Bullet() {}

sf::Sprite Bullet::animate(float tickLength) {
  this->position.y -= 5;
  this->sprite->setPosition(position);
  if (this->position.y < 0) {
    this->processed = true;
  }
  return *(this->sprite);
}
