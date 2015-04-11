#include "Explosion.h"

Explosion::Explosion()
: GameObject(), frames(), currentFrame(0), updateTime(5.f/60.f), timeSinceLastUpdate(0.0f) {
  this->init();
}

Explosion::Explosion(int x, int y, sf::Texture *texture)
: GameObject(x, y, texture), frames(), currentFrame(0), updateTime(5.f/60.f), timeSinceLastUpdate(0.0f) {
  this->init();
}

Explosion::~Explosion() {}

void Explosion::init() {
  this->type = "Explosion";
  for (int y = 0; y < 250; y += 50) {
    for (int x = 0; x < 200; x+= 50) {
      this->frames.push_back(sf::IntRect(x, y, 50, 50));
    }
  }
  this->sprite->setTextureRect(this->frames[this->currentFrame]);
}

void Explosion::move(float tickLength) {
  this->timeSinceLastUpdate += tickLength;
  if (this->timeSinceLastUpdate > this->updateTime) {
    this->timeSinceLastUpdate = 0.0f;
    this->currentFrame++;
    this->sprite->setTextureRect(this->frames[this->currentFrame]);
    if (this->currentFrame > 20) {
      this->processed = true;
    }
  }
}
