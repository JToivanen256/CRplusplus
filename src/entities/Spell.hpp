#ifndef SPELL_HPP
#define SPELL_HPP

#include "Entity.hpp"
#include <SFML/Graphics.hpp>
#include "../players/Player.hpp"

class Spell {
protected:
  float radius_;
  sf::Vector2f centerPosition_;
  int damage_;
  float duration_;
  Player* owner_;

public:
  Spell(int x, int y, float radius, int damage, float duration, Player* owner);

  void cast();

};

#endif