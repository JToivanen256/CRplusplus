#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

#include "Deck.hpp"
#include "Hand.hpp"
#include "SFML/Graphics.hpp"

enum class TowerType { Default };

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
  TowerType towerType_ = TowerType::Default; // In case we have different tower types later
  sf::Color color_;  // Color representing the player in-game

 public:
  void reset(); // Resets player state for a new match
  // Regen elixir over time
  void update(float deltaTime);

  // Actions
  //void drawCard();
  bool playCard(const std::shared_ptr<Card>& card);

  // Deck and Hand
  //void shuffleDeck();
  //void initializeHand();
  void updateHand();

  // Getters
  const std::string& getName() const;
  int getElixir() const;
  const Hand& getHand() const;
  Hand& getHand();
  const Deck& getDeck() const;
  Deck& getDeck();
  const TowerType& getTowerType() const;

  void setColor(const sf::Color& color);

  const sf::Color& getColor() const;
};

#endif