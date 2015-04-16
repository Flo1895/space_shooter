#ifndef BULLET_H_
#define BULLET_H_

#include <string>

#include "GameObject.h"
#include "Utils.h"

#include <SFML/Graphics.hpp>

class Bullet : public GameObject {
private:
  Direction direction;

public:
  Bullet();
  Bullet(int x, int y, sf::Texture *texture, Direction direction);
  ~Bullet();
  void move(float tickLength);
};

#endif // BULLET_H_
