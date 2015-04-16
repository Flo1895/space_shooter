#include "Game.h"

Game::Game()
: window(sf::VideoMode(1280, 720), "Test"),
  stateManager(), highscore("./highscore"), textureManager(),
  ownShip(362, 620, textureManager.get("ownShip")),
  curGameObjects(), curGameObjectsIt(), killCounter(0),
  noBullets(50), bulletBackoff(0.0f), isMovingLeft(false),
  isMovingRight(false), isFiring(false), font(), noBulletsText(),
  killCounterText(), highscoreHeadline(), highscoreEntries() {}

Game::~Game() {}

void Game::run() {
  Utils::initPRNG();

  // load font
  if (!font.loadFromFile("../../font/unispace_bold.ttf")) {
    // logging...
    std::cout << "could not load font" << std::endl;
  }

  // menu items
  // new game
  sf::Text newGameMsg("(N)EW GAME", font, 60);
  newGameMsg.setColor(sf::Color::White);
  newGameMsg.setPosition((1280 - newGameMsg.getLocalBounds().width) / 2,
                         (720 - newGameMsg.getLocalBounds().height) / 2 - 50);
  // highscore
  sf::Text highscoreMsg("(H)IGHSCORE", font, 60);
  highscoreMsg.setColor(sf::Color::White);
  highscoreMsg.setPosition((1280 - highscoreMsg.getLocalBounds().width) / 2,
                           (720 - highscoreMsg.getLocalBounds().height) / 2 + 50);
  
  // display kill counter
  killCounterText.setString(std::to_string(killCounter));
  killCounterText.setFont(font);
  killCounterText.setCharacterSize(50);
  killCounterText.setColor(sf::Color::White);
  killCounterText.setPosition(20, 20);

  // number of bullets
  noBulletsText.setString(std::to_string(noBullets));
  noBulletsText.setFont(font);
  noBulletsText.setCharacterSize(30);
  noBulletsText.setColor(sf::Color::White);
  noBulletsText.setPosition(1200, 20);

  // game over message
  sf::Text gameOverMsg("GAME OVER", font, 60);
  gameOverMsg.setColor(sf::Color::White);
  gameOverMsg.setPosition((1280 - gameOverMsg.getLocalBounds().width) / 2, 320);

  // highscore message
  highscoreHeadline.setString("HIGHSCORE");
  highscoreHeadline.setFont(font);
  highscoreHeadline.setCharacterSize(25);
  highscoreHeadline.setColor(sf::Color::White);
  
  // background image
  sf::Sprite backgroundSprite(*(textureManager.get("background2")));
  float scaleX = 1280.0f/1920.0f;
  float scaleY = 720.0f/1080.0f;
  backgroundSprite.scale(scaleX, scaleY);

  // clock management
  const float timePerFrame = 1.f/60.f;
  sf::Clock clock;
  float tickLength;
  float timeSinceLastUpdate = 0.0f;

  // game loop
  while (window.isOpen()) {
    tickLength = clock.restart().asSeconds();
    timeSinceLastUpdate += tickLength;

    while (timeSinceLastUpdate > timePerFrame) {
      timeSinceLastUpdate -= timePerFrame;
      bulletBackoff -= timePerFrame;

      processEvents();
      update(timePerFrame);
    }

    window.clear();

    // draw background
    window.draw(backgroundSprite);

    if (this->stateManager.getState() == MENU) {
      window.draw(newGameMsg);
      window.draw(highscoreMsg);
    } else if (this->stateManager.getState() == PLAY) {
      int newEnemyShip = Utils::getRandomNumber(1, 150);
      if (newEnemyShip < 3) {
        EnemyShip *e = new EnemyShip(Utils::getRandomNumber(10, 1235),
                                     30, textureManager.get("enemy1"));
        curGameObjects.push_back(e);
      }

      // draw kill counter
      window.draw(killCounterText);
      // draw number of bullets left
      window.draw(noBulletsText);
      // draw own ship
      window.draw(ownShip.getSprite());

      // draw bullets, enemy ships and explosions
      for (auto& gameObject : curGameObjects) {
        window.draw(gameObject->getSprite());
      }  
    } else if (this->stateManager.getState() == GAME_OVER) {
      window.draw(gameOverMsg);
    } else if (this->stateManager.getState() == HIGHSCORE) {
      window.draw(highscoreHeadline);
      for (auto& highscoreEntry : highscoreEntries) {
        window.draw(highscoreEntry);
      }
    }

    window.display();
  }
}

void Game::processEvents() {
  sf::Event event;
  while (window.pollEvent(event)) {
    switch (event.type) {
      case sf::Event::KeyPressed:
        handleInput(event.key.code, true);
        break;
      case sf::Event::KeyReleased:
        handleInput(event.key.code, false);
        break;
      case sf::Event::Closed:
        window.close();
        break;
      default:
        break;
    }
  }
}

void Game::handleInput(sf::Keyboard::Key key, bool isPressed) {
  if (key == sf::Keyboard::N && stateManager.getState() == MENU) {
    this->stateManager.setState(PLAY);
  } else if (key == sf::Keyboard::H && stateManager.getState() == MENU) {
    this->stateManager.setState(HIGHSCORE);
  } else if (key == sf::Keyboard::Left && stateManager.getState() == PLAY) {
    isMovingLeft = isPressed;
  } else if (key == sf::Keyboard::Right && stateManager.getState() == PLAY) {
    isMovingRight = isPressed;
  } else if (key == sf::Keyboard::Space && stateManager.getState() == PLAY) {
    isFiring = isPressed;
  } else if (key == sf::Keyboard::Space && stateManager.getState() == GAME_OVER) {
    this->stateManager.setState(HIGHSCORE);
    highscoreHeadline.setPosition((1280 - highscoreHeadline.getLocalBounds().width) / 2,
                                  (720 - highscoreHeadline.getLocalBounds().height) / 2 - highscore.size() * 50);        
    highscore.add(killCounter, "Player");
    int pos = 1;
    for (auto& highscoreEntryPair : highscore.get()) {
      std::ostringstream highscoreEntryString;
      if (pos < 10) {
        highscoreEntryString << " ";
      }
      highscoreEntryString << pos << ". " << highscoreEntryPair.second << " (" << highscoreEntryPair.first << ")";
      pos++;
      sf::Text highscoreEntry(highscoreEntryString.str(), font, 20);
      highscoreEntry.setColor(sf::Color::White);
      highscoreEntry.setPosition((1280 - highscoreEntry.getLocalBounds().width) / 2,
                                  (720 - highscoreEntry.getLocalBounds().height) / 2 - (highscore.size() - pos) * 30);
      highscoreEntries.push_back(highscoreEntry);
    }
  } else if (key == sf::Keyboard::M && stateManager.getState() == HIGHSCORE) {
    stateManager.setState(MENU);
  }
}

void Game::update(float timePerFrame) {
  // move own ship
  this->ownShip.move(timePerFrame, isMovingLeft, isMovingRight);

  // firing
  if (isFiring && noBullets > 0 && bulletBackoff <= 0.0f) {
    bulletBackoff = 10.f/60.f;
    int x = ownShip.getPositionX() + 32;
    int y = ownShip.getPositionY();
    Bullet *b = new Bullet(x, y, textureManager.get("bullet"), UP);
    curGameObjects.push_back(b);
    noBullets--;
    noBulletsText.setString(std::to_string(noBullets));
  }
    
  // move bullets, enemy ships and explosions and check if they are processed
  std::vector<Bullet*> newEnemyBullets;
  for (curGameObjectsIt = curGameObjects.begin();
       curGameObjectsIt != curGameObjects.end();) {
    (*curGameObjectsIt)->move(timePerFrame);
    if ((*curGameObjectsIt)->getType() == "EnemyShip") {
      EnemyShip* enemyShip = dynamic_cast<EnemyShip*>(*curGameObjectsIt);
      if (enemyShip->getFireBackoff() <= 0.0f) {
        enemyShip->resetFireBackoff();
        int x = enemyShip->getPositionX() + 20;
        int y = enemyShip->getPositionY() + 60;
        Bullet *b = new Bullet(x, y, textureManager.get("bullet"), DOWN);
        newEnemyBullets.push_back(b);
      } else {
        enemyShip->reduceFireBackoff(timePerFrame);
      }
    }
    if ((*curGameObjectsIt)->isProcessed()) {
      if ((*curGameObjectsIt)->getType() == "Bullet") {
        noBullets++;
        noBulletsText.setString(std::to_string(noBullets));        
      }
      delete *curGameObjectsIt;
      curGameObjectsIt = curGameObjects.erase(curGameObjectsIt);
    } else {
      ++curGameObjectsIt;
    }
  }
  curGameObjects.insert(curGameObjects.end(),
                      newEnemyBullets.begin(),
                      newEnemyBullets.end());

  std::vector<Explosion*> newExplosions;
  for (auto& gameObject1 : curGameObjects) {
    // check collision between enemy ship and own ship
    if (gameObject1->getType() == "EnemyShip" && ownShip.intersects(gameObject1)) {
      this->stateManager.setState(GAME_OVER);
    }
    // check collision between enemy ship and bullet
    for (auto& gameObject2 : curGameObjects) {
      if (gameObject1->getType() == "EnemyShip" &&
          gameObject2->getType() == "Bullet" &&
          gameObject1->intersects(gameObject2)) {
        gameObject1->setProcessed(true);
        gameObject2->setProcessed(true);
        Explosion *ex = new Explosion(gameObject1->getPositionX(),
                                      gameObject1->getPositionY(),
                                      textureManager.get("explosion"));
        newExplosions.push_back(ex);
        killCounter++;
        killCounterText.setString(std::to_string(killCounter));
      }
    }
  }
  curGameObjects.insert(curGameObjects.end(),
                        newExplosions.begin(),
                        newExplosions.end());
}