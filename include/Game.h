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
/*  
  std::vector<Bullet*> curBullets;
  std::vector<Bullet*>::iterator curBulletsIt;
  std::vector<EnemyShip*> curEnemyShips;
  std::vector<EnemyShip*>::iterator curEnemyShipsIt;
  std::vector<Explosion*> curExplosions;
  std::vector<Explosion*>::iterator curExplosionsIt;
*/

  int killCounter;
  int noBullets;
  float bulletBackoff;
  bool isMovingLeft;
  bool isMovingRight;
  bool isFiring;

  sf::Text noBulletsText;
  sf::Text killCounterText;

  void processEvents();
  void handleInput(sf::Keyboard::Key key, bool isPressed);
  void update(float timePerFrame);
};

#endif // GAME_H_
