#ifndef POWER_UP_H_
#define POWER_UP_H_

#include <string>

#include "GameObject.h"

#include <SFML/Graphics.hpp>

class PowerUp : public GameObject {
private:
  int velocity;

public:
  PowerUp();
  PowerUp(int x, int y, std::string type, sf::Texture *texture);
  ~PowerUp();
  void move(float tickLength);
};

#endif // POWER_UP_H_