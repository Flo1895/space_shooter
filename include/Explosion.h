#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include "GameObject.h"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <vector>

class Explosion : public GameObject {
private:
  void init();
  std::vector<sf::IntRect> frames;
  int currentFrame;
  float updateTime;
  float timeSinceLastUpdate;

public:
  Explosion();
  Explosion(int x, int y, sf::Texture *texture);
  ~Explosion();
  sf::Sprite animate(float tickLength);
};

#endif // EXPLOSION_H_
