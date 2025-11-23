#ifndef CARD_HPP
#define CARD_HPP

#include <string>

class Card {
 public:
  Card(const std::string& name, int cost, bool isSpell);
  virtual ~Card() = default;

  const std::string& getName() const;
  int getCost() const;
  bool isSpell() const;
  const std::string& getSpritePath() const;

 private:
  std::string name_;
  int cost_;
  bool isSpell_;
  std::string spritePath_;  // Path to the sprite relative to assets/sprites/
};

#endif