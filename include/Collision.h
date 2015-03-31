#ifndef COLLISION_H_
#define COLLISION_H_

#include <SFML/System.hpp>

class Collision {
public:
  static bool checkBox(sf::Vector2f pos1, sf::Vector2u size1,
                       sf::Vector2f pos2, sf::Vector2u size2);
};

#endif // COLLISION_H_
