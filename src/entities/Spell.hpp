#ifndef SPELL_HPP
#define SPELL_HPP

#include "Entity.hpp"
#include <SFML/Graphics.hpp>

struct Pos {
  int x;
  int y;
};

class Spell {
protected:
  float radius_;
  Pos centerPosition_;
  int damage_;
  float duration_;

public:
  Spell(int x, int y, float radius, int damage, float duration);

  void cast();

};

#endif