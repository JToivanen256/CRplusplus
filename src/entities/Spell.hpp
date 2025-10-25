#ifndef SPELL_HPP
#define SPELL_HPP

#include "Entity.hpp"

class Spell : public Entity {
protected:
  float radius_;
  int damage_;
  float duration_;

public:
  Spell(int x, int y, float radius, int damage, float duration);


  void cast();

};

#endif