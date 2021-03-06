#ifndef GAME_H_
#define GAME_H_

#include "Utils.h"
#include "StateManager.h"
#include "Highscore.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Ship.h"
#include "Bullet.h"
#include "EnemyShip.h"
#include "Explosion.h"
#include "PowerUp.h"

#include <iostream>
#include <vector>

class Game {
public:
  Game();
  ~Game();
  void run();

private:
  sf::RenderWindow window;

  StateManager stateManager;
  Highscore highscore;
  TextureManager textureManager;
  Ship ownShip;
  std::vector<GameObject*> curGameObjects;
  std::vector<GameObject*>::iterator curGameObjectsIt;

  int killCounter;
  int noBullets;
  float bulletBackoff;
  float extraFireBackoff;
  bool isMovingUp;
  bool isMovingDown;
  bool isMovingLeft;
  bool isMovingRight;
  bool isFiring;

  sf::Font font;
  sf::Text newGameMsg;
  sf::Text highscoreMsg;
  sf::Text killCounterText;
  sf::Text livesText;
  sf::Text gameOverMsg;

  sf::Sprite backgroundSprite;

  void init();
  void processEvents();
  void handleInput(sf::Keyboard::Key key, bool isPressed);
  void update(float timePerFrame);
  void draw();
  void processEnemyHit();
  void updateHighscore();
  void reset();
};

#endif // GAME_H_
