#include "Bullet.h"

Bullet::Bullet()
: GameObject() {
  this->type = "Bullet";
}

Bullet::Bullet(int x, int y, sf::Texture *texture, Direction direction)
: GameObject(x, y, texture) {
  if (direction == DOWN) {
  	this->type = "EnemyBullet";
    this->velocity = Utils::getRandomNumber(200, 300);
  } else {
    this->type = "Bullet";
    this->velocity = 300;
  }
  this->direction = direction;
}

Bullet::~Bullet() {}

void Bullet::move(float tickLength) {
  if (this->direction == UP) {
    this->position.y -= tickLength * this->velocity;
  } else {
  	this->position.y += tickLength * this->velocity;
  }
  this->sprite->setPosition(position);
  if (this->position.y < 0) {
    this->processed = true;
  }
}
