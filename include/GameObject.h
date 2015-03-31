#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include <string>

#include <SFML/Graphics.hpp>

class GameObject {
protected:
  sf::Vector2f position;
  sf::Texture texture;
  sf::Sprite *sprite;
  bool processed;

public:
  GameObject();
  GameObject(int x, int y, std::string texturePath);
  ~GameObject();
  int getPositionX();
  int getPositionY();
  void setProcessed(bool processed);
  bool isProcessed();

  virtual sf::Sprite animate() = 0;
};

#endif // GAME_OBJECT_H_
