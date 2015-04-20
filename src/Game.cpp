#include "Game.h"

Game::Game()
: window(sf::VideoMode(1280, 720), "Test"),
  stateManager(),
  highscore("./highscore"),
  textureManager(),
  ownShip(362, 620, textureManager.get("ownShip")),
  curGameObjects(),
  curGameObjectsIt(),
  killCounter(0),
  noBullets(50),
  bulletBackoff(0.0f),
  extraFireBackoff(0.0f),
  isMovingUp(false),
  isMovingDown(false),
  isMovingLeft(false),
  isMovingRight(false),
  isFiring(false),
  font(),
  newGameMsg(),
  highscoreMsg(),
  noBulletsText(),
  killCounterText(),
  livesText(),
  gameOverMsg(),
  backgroundSprite() {
    this->init();
  }

Game::~Game() {}

void Game::init() {
  Utils::initPRNG();

  // load font
  if (!this->font.loadFromFile("../../font/unispace_bold.ttf")) {
    // logging...
    std::cout << "could not load font" << std::endl;
  }

  // menu items
  // new game
  this->newGameMsg.setString("(N)EW GAME");
  this->newGameMsg.setFont(this->font);
  this->newGameMsg.setCharacterSize(60);
  this->newGameMsg.setColor(sf::Color::White);
  this->newGameMsg.setPosition((1280 - newGameMsg.getLocalBounds().width) / 2,
                               (720 - newGameMsg.getLocalBounds().height) / 2 - 50);
  // highscore
  std::ostringstream highscoreString;
  highscoreString << "BEST: " << highscore.get();
  this->highscoreMsg.setString(highscoreString.str());
  this->highscoreMsg.setFont(this->font);
  this->highscoreMsg.setCharacterSize(60);
  this->highscoreMsg.setColor(sf::Color::White);
  this->highscoreMsg.setPosition((1280 - highscoreMsg.getLocalBounds().width) / 2,
                                 (720 - highscoreMsg.getLocalBounds().height) / 2 + 50);
  
  // display kill counter
  this->killCounterText.setString(std::to_string(this->killCounter));
  this->killCounterText.setFont(this->font);
  this->killCounterText.setCharacterSize(50);
  this->killCounterText.setColor(sf::Color::White);
  this->killCounterText.setPosition(20, 20);

  // display number of lives for own ship
  this->livesText.setString(std::to_string(this->ownShip.getLives()));
  this->livesText.setFont(this->font);
  this->livesText.setCharacterSize(30);
  this->livesText.setColor(sf::Color::White);
  this->livesText.setPosition(1000, 20);

  // number of bullets
  this->noBulletsText.setString(std::to_string(this->noBullets));
  this->noBulletsText.setFont(this->font);
  this->noBulletsText.setCharacterSize(30);
  this->noBulletsText.setColor(sf::Color::White);
  this->noBulletsText.setPosition(1200, 20);

  // game over message
  this->gameOverMsg.setString("GAME OVER");
  this->gameOverMsg.setFont(this->font);
  this->gameOverMsg.setCharacterSize(60);
  this->gameOverMsg.setColor(sf::Color::White);
  this->gameOverMsg.setPosition((1280 - gameOverMsg.getLocalBounds().width) / 2, 320);
  
  // background image
  this->backgroundSprite.setTexture(*(this->textureManager.get("background2")));
  float scaleX = 1280.0f/1920.0f;
  float scaleY = 720.0f/1080.0f;
  this->backgroundSprite.scale(scaleX, scaleY);
}

void Game::run() {
  // clock management
  const float timePerFrame = 1.f/60.f;
  sf::Clock clock;
  float tickLength;
  float timeSinceLastUpdate = 0.0f;

  // game loop
  while (this->window.isOpen()) {
    tickLength = clock.restart().asSeconds();
    timeSinceLastUpdate += tickLength;

    while (timeSinceLastUpdate > timePerFrame) {
      timeSinceLastUpdate -= timePerFrame;
      this->bulletBackoff -= timePerFrame;
      if (this->ownShip.getExtraFire()) {
        this->extraFireBackoff -= timePerFrame;
        if (this->extraFireBackoff <= 0.0f) {
          this->ownShip.setExtraFire(false);
        }
      }

      this->processEvents();
      this->update(timePerFrame);
    }

    this->draw();

  }
}

void Game::processEvents() {
  sf::Event event;
  while (this->window.pollEvent(event)) {
    switch (event.type) {
      case sf::Event::KeyPressed:
        handleInput(event.key.code, true);
        break;
      case sf::Event::KeyReleased:
        handleInput(event.key.code, false);
        break;
      case sf::Event::Closed:
        this->window.close();
        break;
      default:
        break;
    }
  }
}

void Game::handleInput(sf::Keyboard::Key key, bool isPressed) {
  switch (this->stateManager.getState()) {
    case MENU:
      if (key == sf::Keyboard::N) {
        this->reset();
        this->stateManager.setState(PLAY);
      }
      break;
    case PLAY:
      if (key == sf::Keyboard::Up) {
        this->isMovingUp = isPressed;
      }
      if (key == sf::Keyboard::Down) {
        this->isMovingDown = isPressed;
      }
      if (key == sf::Keyboard::Left) {
        this->isMovingLeft = isPressed;
      }
      if (key == sf::Keyboard::Right) {
        this->isMovingRight = isPressed;
      }
      if (key == sf::Keyboard::Space) {
        this->isFiring = isPressed;
      }
      break;
    case GAME_OVER:
      if (key == sf::Keyboard::Space) {
        this->updateHighscore();
        this->stateManager.setState(MENU);
      }
      break;
  }
}

void Game::update(float timePerFrame) {
  // move own ship
  this->ownShip.move(timePerFrame, this->isMovingUp, this->isMovingDown,
                     this->isMovingLeft, this->isMovingRight);

  // firing
  if (this->isFiring && this->noBullets > 0 && this->bulletBackoff <= 0.0f) {
    this->bulletBackoff = 10.f/60.f;
    int x = this->ownShip.getPositionX() + 32;
    int y = this->ownShip.getPositionY();
    Bullet *b = new Bullet(x, y, this->textureManager.get("bullet"), UP);
    this->curGameObjects.push_back(b);
    if (this->ownShip.getExtraFire()) {
      Bullet *b2 = new Bullet(x + 27, y + 10, this->textureManager.get("bullet"), UP);
      this->curGameObjects.push_back(b2);
      Bullet *b3 = new Bullet(x - 27, y + 10, this->textureManager.get("bullet"), UP);
      this->curGameObjects.push_back(b3);
      this->noBullets -= 2;
    }
    this->noBullets--;
    this->noBulletsText.setString(std::to_string(this->noBullets));
  }
    
  // move bullets, enemy ships and explosions and check if they are processed
  std::vector<Bullet*> newEnemyBullets;
  for (this->curGameObjectsIt = this->curGameObjects.begin();
       this->curGameObjectsIt != this->curGameObjects.end();) {
    (*this->curGameObjectsIt)->move(timePerFrame);
    if ((*this->curGameObjectsIt)->getType() == "EnemyShip") {
      EnemyShip* enemyShip = dynamic_cast<EnemyShip*>(*this->curGameObjectsIt);
      if (enemyShip->getFireBackoff() <= 0.0f) {
        enemyShip->resetFireBackoff();
        int x = enemyShip->getPositionX() + 20;
        int y = enemyShip->getPositionY() + 60;
        Bullet *b = new Bullet(x, y, this->textureManager.get("bullet"), DOWN);
        newEnemyBullets.push_back(b);
      } else {
        enemyShip->reduceFireBackoff(timePerFrame);
      }
    }
    if ((*this->curGameObjectsIt)->isProcessed()) {
      if ((*this->curGameObjectsIt)->getType() == "Bullet") {
        noBullets++;
        this->noBulletsText.setString(std::to_string(this->noBullets));        
      }
      delete *this->curGameObjectsIt;
      this->curGameObjectsIt = this->curGameObjects.erase(this->curGameObjectsIt);
    } else {
      ++this->curGameObjectsIt;
    }
  }
  this->curGameObjects.insert(this->curGameObjects.end(),
                              newEnemyBullets.begin(),
                              newEnemyBullets.end());

  std::vector<GameObject*> newGameObjects;
  for (auto& gameObject1 : this->curGameObjects) {
    // check collision between enemy ship and bullet
    for (auto& gameObject2 : this->curGameObjects) {
      if (gameObject1->getType() == "EnemyShip" &&
          gameObject2->getType() == "Bullet" &&
          gameObject1->intersects(gameObject2)) {
        gameObject1->setProcessed(true);
        gameObject2->setProcessed(true);
        Explosion *ex = new Explosion(gameObject1->getPositionX(),
                                      gameObject1->getPositionY(),
                                      this->textureManager.get("explosion"));
        newGameObjects.push_back(ex);
        PowerUp *lp;
        switch (Utils::getRandomNumber(1, 2)) {
          case 1:
            lp = new PowerUp(gameObject1->getPositionX(),
                             gameObject1->getPositionY(),
                             "LivePowerUp",
                             this->textureManager.get("livePowerUp"));
          case 2:
            lp = new PowerUp(gameObject1->getPositionX(),
                             gameObject1->getPositionY(),
                             "WeaponPowerUp",
                             this->textureManager.get("weaponPowerUp"));
        }
        newGameObjects.push_back(lp);
        this->killCounter++;
        this->killCounterText.setString(std::to_string(this->killCounter));
      }
    }
    // check collision between enemy ship and own ship
    if (gameObject1->getType() == "EnemyShip" && ownShip.intersects(gameObject1)) {
      gameObject1->setProcessed(true);
      this->processEnemyHit();
    }
    // check collision between enemy bullet and own ship
    if (gameObject1->getType() == "EnemyBullet" && ownShip.intersects(gameObject1)) {
      gameObject1->setProcessed(true);
      this->processEnemyHit();
    }
    // check collision between live powerUp and own ship
    if (gameObject1->getType() == "LivePowerUp" && ownShip.intersects(gameObject1)) {
      gameObject1->setProcessed(true);
      this->ownShip.resetLives();
      this->livesText.setString(std::to_string(this->ownShip.getLives()));
    }
    // check collision between weapon powerUp and own ship
    if (gameObject1->getType() == "WeaponPowerUp" && ownShip.intersects(gameObject1)) {
      gameObject1->setProcessed(true);
      this->extraFireBackoff = 300.f/60.f;
      this->ownShip.setExtraFire(true);
    }
  }
  this->curGameObjects.insert(this->curGameObjects.end(),
                              newGameObjects.begin(),
                              newGameObjects.end());
}

void Game::draw() {
  this->window.clear();

  // draw background
  this->window.draw(this->backgroundSprite);

  if (this->stateManager.getState() == MENU) {
    this->window.draw(this->newGameMsg);
    this->window.draw(this->highscoreMsg);
  } else if (this->stateManager.getState() == PLAY) {
    int newEnemyShip = Utils::getRandomNumber(1, 150);
    if (newEnemyShip < 3) {
      EnemyShip *e = new EnemyShip(Utils::getRandomNumber(10, 1235),
                                   30, this->textureManager.getRandomShip());
      this->curGameObjects.push_back(e);
    }

    // draw kill counter
    this->window.draw(this->killCounterText);
    // draw number of lives of own ship
    this->window.draw(this->livesText);
    // draw number of bullets left
    this->window.draw(this->noBulletsText);
    // draw own ship
    this->window.draw(this->ownShip.getSprite());

    // draw bullets, enemy ships and explosions
    for (auto& gameObject : this->curGameObjects) {
      this->window.draw(gameObject->getSprite());
    }  
  } else if (this->stateManager.getState() == GAME_OVER) {
    this->window.draw(this->gameOverMsg);
  }  

  this->window.display();
}

void Game::processEnemyHit() {
  this->ownShip.decreaseLives();
  this->livesText.setString(std::to_string(this->ownShip.getLives()));
  if (this->ownShip.getLives() == 0) {
    this->stateManager.setState(GAME_OVER);
  }
}

void Game::updateHighscore() {
  if (this->killCounter > this->highscore.get()) {
    this->highscore.set(this->killCounter);
    std::ostringstream highscoreString;
    highscoreString << "BEST: " << highscore.get();
    this->highscoreMsg.setString(highscoreString.str());
  }  
}

void Game::reset() {
  // delete all old game objects
  for (curGameObjectsIt = curGameObjects.begin();
       curGameObjectsIt != curGameObjects.end();) {
    delete *curGameObjectsIt;
    curGameObjectsIt = curGameObjects.erase(curGameObjectsIt);
  }

  // reset position and lives of own ship
  sf::Vector2f ownShipPosition(362, 620);
  this->ownShip.setPosition(ownShipPosition);
  this->ownShip.move(0.0f);
  this->ownShip.resetLives();
  this->livesText.setString(std::to_string(this->ownShip.getLives()));

  // reset other values
  this->killCounter = 0;
  this->killCounterText.setString(std::to_string(this->killCounter));
  this->noBullets = 50;
  this->noBulletsText.setString(std::to_string(this->noBullets));
  this->bulletBackoff = 0.0f;
  this->isMovingUp = false;
  this->isMovingDown = false;
  this->isMovingRight = false;
  this->isMovingLeft = false;
  this->isFiring = false;
}
