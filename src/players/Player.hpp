#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

#include "Deck.hpp"
#include "Hand.hpp"
#include "../entities/Tower.hpp"


class Player { 
public:
  Player(const std::string& name, Deck deck);
protected:
  int elixir_;
  std::string name_;
  Deck deck_;
  Hand hand_ = Hand();
//  Tower& kingTower_;
//  Tower& firstTower_;
//  Tower& secondTower_;
public:

  // Actions
  void drawCard();
  void playCard(const Card& card);
  void gainElixir(int amount);
  void spendElixir(int amount);

  // Deck and Hand 
  void shuffleDeck();
  void initializeHand();

  // Getters
  const std::string& getName() const;
  int getElixir() const;
  const Hand& getHand() const;

};

#endif