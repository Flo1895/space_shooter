#ifndef BULLET_H_
#define BULLET_H_

#include <string>

#include "GameObject.h"

#include <SFML/Graphics.hpp>

class Bullet : public GameObject {
public:
  Bullet();
  Bullet(int x, int y, sf::Texture *texture);
  ~Bullet();

  sf::Sprite animate(float tickLength);
};

#endif // BULLET_H_
