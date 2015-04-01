#include "TextureManager.h"

TextureManager::TextureManager() {}

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
