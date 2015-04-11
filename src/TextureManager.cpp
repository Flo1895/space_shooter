#include "TextureManager.h"

TextureManager::TextureManager() {
  this->add("background1", "../../graphics/background1.png");
  this->add("background2", "../../graphics/background2.png");
  this->add("ownShip", "../../graphics/ownShip.png");
  this->add("enemy1", "../../graphics/enemy1.png");
  this->add("bullet", "../../graphics/bullet.png");
  this->add("explosion", "../../graphics/explosion.png");
}

TextureManager::~TextureManager() {
  std::map<std::string, sf::Texture*>::iterator texturesIt;
  for (texturesIt = textures.begin(); texturesIt != textures.end(); ++texturesIt) {
    delete texturesIt->second;
  }
}

void TextureManager::add(std::string name, std::string path) {
  sf::Texture *texture = new sf::Texture();
  if (!texture->loadFromFile(path)) {
    //return EXIT_FAILURE;
    // TODO throw exception and return EXIT_FAILURE in main
  }
  texture->setSmooth(true);
  this->textures[name] = texture;
}

sf::Texture* TextureManager::get(std::string name) {
  // TODO error handling when 'name' is not found
  return this->textures[name];
}
