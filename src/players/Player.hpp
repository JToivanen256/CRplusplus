#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

#include "Deck.hpp"
#include "Hand.hpp"

enum class TowerType {
  Default
};

class Player {
 public:
  Player(const std::string& name, Deck deck);

 protected:
  int elixir_;
  std::string name_;
  Deck deck_;
  Hand hand_;
  float elixirRegenRate_ = 1.0f;
  float elixirTimer_ = 0.0f;
  TowerType towerType_ = TowerType::Default;

 public:
  // Regen elixir over time
  void update(float deltaTime);

  // Actions
  void drawCard();
  void playCard(const Card& card);

  // Deck and Hand
  void shuffleDeck();
  void initializeHand();

  // Getters
  const std::string& getName() const;
  int getElixir() const;
  const Hand& getHand() const;
  const TowerType& getTowerType() const;
};

#endif