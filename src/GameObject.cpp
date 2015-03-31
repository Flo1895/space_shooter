#include "GameObject.h"

GameObject::GameObject()
: position(), texture(), sprite() {}

GameObject::GameObject(int x, int y, std::string texturePath)
: position(x, y), size(), texture(), sprite() {
  if (!this->texture.loadFromFile(texturePath)) {
    // some nice logging or something like this 
  }
  this->size = this->texture.getSize();
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

sf::Vector2f GameObject::getPosition() {
  return this->position;
}

sf::Vector2u GameObject::getSize() {
  return this->size;
}

bool GameObject::intersects(GameObject *gameObject) {
  return Collision::checkBox(this->position, this->size,
                             gameObject->getPosition(), gameObject->getSize());
}

void GameObject::setProcessed(bool processed) {
  this->processed = processed;
}

bool GameObject::isProcessed() {
  return this->processed;
}
