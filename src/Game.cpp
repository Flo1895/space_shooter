#include "Game.h"

Game::Game()
: window(sf::VideoMode(1280, 720), "Test"),
  stateManager(), highscore("./highscore"), textureManager(),
  ownShip(362, 620, textureManager.get("ownShip")),
  curGameObjects(), curGameObjectsIt(), killCounter(0),
  noBullets(50), bulletBackoff(0.0f), isMovingLeft(false),
  isMovingRight(false), isFiring(false), font(), newGameMsg(),
  highscoreMsg(), noBulletsText(), killCounterText(),
  gameOverMsg(), highscoreHeadline(), highscoreEntries(), backgroundSprite() {
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
  this->highscoreMsg.setString("(H)IGHSCORE");
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

  // highscore message
  this->highscoreHeadline.setString("HIGHSCORE");
  this->highscoreHeadline.setFont(this->font);
  this->highscoreHeadline.setCharacterSize(25);
  this->highscoreHeadline.setColor(sf::Color::White);
  
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
  if (key == sf::Keyboard::N && this->stateManager.getState() == MENU) {
    this->reset();
    this->stateManager.setState(PLAY);
  } else if (key == sf::Keyboard::H && this->stateManager.getState() == MENU) {
    this->stateManager.setState(HIGHSCORE);
  } else if (key == sf::Keyboard::Left && this->stateManager.getState() == PLAY) {
    this->isMovingLeft = isPressed;
  } else if (key == sf::Keyboard::Right && this->stateManager.getState() == PLAY) {
    this->isMovingRight = isPressed;
  } else if (key == sf::Keyboard::Space && this->stateManager.getState() == PLAY) {
    this->isFiring = isPressed;
  } else if (key == sf::Keyboard::Space && this->stateManager.getState() == GAME_OVER) {
    this->stateManager.setState(HIGHSCORE);
    highscoreHeadline.setPosition((1280 - highscoreHeadline.getLocalBounds().width) / 2,
                                  (720 - highscoreHeadline.getLocalBounds().height) / 2 - this->highscore.size() * 50);        
    highscore.add(this->killCounter, "Player");
    int pos = 1;
    for (auto& highscoreEntryPair : this->highscore.get()) {
      std::ostringstream highscoreEntryString;
      if (pos < 10) {
        highscoreEntryString << " ";
      }
      highscoreEntryString << pos << ". " << highscoreEntryPair.second << " (" << highscoreEntryPair.first << ")";
      pos++;
      sf::Text highscoreEntry(highscoreEntryString.str(), font, 20);
      highscoreEntry.setColor(sf::Color::White);
      highscoreEntry.setPosition((1280 - highscoreEntry.getLocalBounds().width) / 2,
                                  (720 - highscoreEntry.getLocalBounds().height) / 2 - (this->highscore.size() - pos) * 30);
      highscoreEntries.push_back(highscoreEntry);
    }
  } else if (key == sf::Keyboard::M && this->stateManager.getState() == HIGHSCORE) {
    this->stateManager.setState(MENU);
  }
}

void Game::update(float timePerFrame) {
  // move own ship
  this->ownShip.move(timePerFrame, this->isMovingLeft, this->isMovingRight);

  // firing
  if (this->isFiring && this->noBullets > 0 && this->bulletBackoff <= 0.0f) {
    this->bulletBackoff = 10.f/60.f;
    int x = ownShip.getPositionX() + 32;
    int y = ownShip.getPositionY();
    Bullet *b = new Bullet(x, y, this->textureManager.get("bullet"), UP);
    this->curGameObjects.push_back(b);
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

  std::vector<Explosion*> newExplosions;
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
        newExplosions.push_back(ex);
        this->killCounter++;
        this->killCounterText.setString(std::to_string(this->killCounter));
      }
    }
    // check collision between enemy ship and own ship
    if (gameObject1->getType() == "EnemyShip" && ownShip.intersects(gameObject1)) {
      this->stateManager.setState(GAME_OVER);
    }
    // check collision between enemy bullet and own ship
    if (gameObject1->getType() == "EnemyBullet" && ownShip.intersects(gameObject1)) {
      this->stateManager.setState(GAME_OVER);
    }
  }
  this->curGameObjects.insert(this->curGameObjects.end(),
                              newExplosions.begin(),
                              newExplosions.end());
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
                                   30, this->textureManager.get("enemy1"));
      this->curGameObjects.push_back(e);
    }

    // draw kill counter
    this->window.draw(this->killCounterText);
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
  } else if (this->stateManager.getState() == HIGHSCORE) {
    this->window.draw(this->highscoreHeadline);
    for (auto& highscoreEntry : this->highscoreEntries) {
      this->window.draw(highscoreEntry);
    }
  }

  this->window.display();
}

void Game::reset() {
  // delete all old game objects
  std::cout << this->curGameObjects.size() << std::endl;
  /*
  for (curGameObjectsIt = curGameObjects.begin();
       curGameObjectsIt != curGameObjects.end();) {
    delete *curGameObjectsIt;
    curGameObjectsIt = curGameObjects.erase(curGameObjectsIt);
  }
  */

  // reset position of own ship
  sf::Vector2f ownShipPosition(362, 620);
  this->ownShip.setPosition(ownShipPosition);

  // reset other values
  this->killCounter = 0;
  this->killCounterText.setString(std::to_string(this->killCounter));
  this->noBullets = 50;
  this->noBulletsText.setString(std::to_string(this->noBullets));
  this->bulletBackoff = 0.0f;
  this->isMovingRight = false;
  this->isMovingLeft = false;
  this->isFiring = false;
}
