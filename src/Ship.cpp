#include "Ship.h"

Ship::Ship()
: GameObject() {}

Ship::Ship(int x, int y, sf::Texture *texture)
: GameObject(x, y, texture) {}

Ship::~Ship() {}

void Ship::move(sf::Keyboard::Key key) {
  if (key == sf::Keyboard::Left) {
    // move left if key left was pressed
    if (this->position.x > 10) {
      this->position.x -= 5;
      this->sprite->setPosition(this->position);
    }
  }
  else if (key == sf::Keyboard::Right) {
    // move right if key right was pressed
    if (this->position.x < 1235) {
      this->position.x += 5;
      this->sprite->setPosition(this->position);
    }
  }
}

sf::Sprite Ship::animate(float tickLength) {
  return *(this->sprite);
}
