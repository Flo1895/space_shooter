#ifndef LIVE_POWER_UP_H_
#define LIVE_POWER_UP_H_

#include <string>

#include "GameObject.h"

#include <SFML/Graphics.hpp>

class LivePowerUp : public GameObject {
private:
  int velocity;

public:
  LivePowerUp();
  LivePowerUp(int x, int y, sf::Texture *texture);
  ~LivePowerUp();
  void move(float tickLength);
};

#endif // LIVE_POWER_UP_H_