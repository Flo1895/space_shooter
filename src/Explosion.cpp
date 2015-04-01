#include "Explosion.h"

Explosion::Explosion()
: GameObject(), frames(), currentFrame(0), clock() {
  this->init();
}

Explosion::Explosion(int x, int y, std::string texturePath)
: GameObject(x, y, texturePath), frames(), currentFrame(0), clock() {
  this->init();
}

Explosion::~Explosion() {}

void Explosion::init() {
  for (int y = 0; y < 250; y += 50) {
    for (int x = 0; x < 200; x+= 50) {
      this->frames.push_back(sf::IntRect(x, y, 50, 50));
    }
  }
  this->sprite->setTextureRect(this->frames[this->currentFrame]);
  sf::Clock clock;
}

sf::Sprite Explosion::animate() {
  if (this->clock.getElapsedTime().asMilliseconds() > 50) {
    this->clock.restart();
    this->currentFrame++;
    this->sprite->setTextureRect(this->frames[this->currentFrame]);
    if (this->currentFrame > 20) {
      this->processed = true;
    }
  }
  return *(this->sprite);
}
