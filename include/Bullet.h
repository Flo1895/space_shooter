#ifndef BULLET_H_
#define BULLET_H_

#include <string>

#include "GameObject.h"

#include <SFML/Graphics.hpp>

class Bullet : public GameObject {
public:
  Bullet();
  Bullet(int x, int y, std::string texturePath);
  ~Bullet();

  sf::Sprite animate();
};

#endif // BULLET_H_
