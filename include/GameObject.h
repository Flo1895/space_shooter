#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include <string>

#include <SFML/Graphics.hpp>

#include "Collision.h"

class GameObject {
protected:
  sf::Vector2f position;
  sf::Vector2u size;
  sf::Texture *texture;
  sf::Sprite *sprite;
  bool processed;

public:
  GameObject();
  GameObject(int x, int y, sf::Texture *texture);
  ~GameObject();
  int getPositionX();
  int getPositionY();
  sf::Vector2f getPosition();
  sf::Vector2u getSize();
  bool intersects(GameObject *gameObject);
  void setProcessed(bool processed);
  bool isProcessed();

  virtual sf::Sprite animate(float tickLength) = 0;
};

#endif // GAME_OBJECT_H_
