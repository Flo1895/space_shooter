#include "Collision.h"

bool Collision::checkBox(sf::Vector2f pos1, sf::Vector2u size1,
                         sf::Vector2f pos2, sf::Vector2u size2) {
  if (pos1.x < pos2.x + size2.x &&
      pos1.x + size1.x > pos2.x &&
      pos1.y < pos2.y + size2.y &&
      size1.y + pos1.y > pos2.y) {
    return true;
  }

  return false;
}
