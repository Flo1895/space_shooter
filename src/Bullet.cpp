#include "Bullet.h"

Bullet::Bullet()
: GameObject() {}

Bullet::Bullet(int x, int y, std::string texturePath)
: GameObject(x, y, texturePath) {}

Bullet::~Bullet() {}

sf::Sprite Bullet::animate() {
  this->position.y -= 5;
  this->sprite->setPosition(position);
  if (this->position.y < 0) {
    this->processed = true;
  }
  return *(this->sprite);
}
