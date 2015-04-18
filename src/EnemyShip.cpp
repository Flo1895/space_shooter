#include "EnemyShip.h"

EnemyShip::EnemyShip()
: GameObject(), fireBackoff(0.f) {
  this->type = "EnemyShip";
}

EnemyShip::EnemyShip(int x, int y, sf::Texture *texture)
: GameObject(x, y, texture), fireBackoff(0.f) {
  this->type = "EnemyShip";
}

EnemyShip::~EnemyShip() {}

void EnemyShip::move(float tickLength) {
  this->position.y += tickLength * 150;
  this->sprite->setPosition(position);
  if (this->position.y > 600) {
    this->processed = true;
  }
}

float EnemyShip::getFireBackoff() {
  return this->fireBackoff;
}

void EnemyShip::reduceFireBackoff(float timePerFrame) {
  this->fireBackoff -= timePerFrame;
}

void EnemyShip::resetFireBackoff() {
  this->fireBackoff = 120.f/60.f;
}
