#include "GameObject.h"

GameObject::GameObject()
: position(), texture(), sprite() {}

GameObject::GameObject(int x, int y, std::string texturePath)
: position(x, y), texture(), sprite() {
  if (!this->texture.loadFromFile(texturePath)) {
    // some nice logging or something like this 
  }
  this->texture.setSmooth(true);
  this->sprite = new sf::Sprite(texture);
  this->sprite->setPosition(this->position);
  this->processed = false;
}

GameObject::~GameObject() {
  delete sprite;
}

int GameObject::getPositionX() {
  return this->position.x;
}

int GameObject::getPositionY() {
  return this->position.y;
}

void GameObject::setProcessed(bool processed) {
  this->processed = processed;
}

bool GameObject::isProcessed() {
  return this->processed;
}
