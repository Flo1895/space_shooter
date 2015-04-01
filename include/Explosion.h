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
  sf::Clock clock;

public:
  Explosion();
  Explosion(int x, int y, std::string texturePath);
  ~Explosion();
  sf::Sprite animate();
};

#endif // EXPLOSION_H_
