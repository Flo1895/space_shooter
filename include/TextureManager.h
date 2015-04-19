#ifndef TEXTURE_MANAGER_H_
#define TEXTURE_MANAGER_H_

#include "Utils.h"

#include <map>
#include <string>

#include <SFML/Graphics.hpp>

class TextureManager {
private:
  std::map<std::string, sf::Texture*> textures;

public:
  TextureManager();
  ~TextureManager();
  void add(std::string name, std::string path);
  sf::Texture* get(std::string);
  sf::Texture* getRandomShip();
};

#endif // TEXTURE_MANAGER_H_
