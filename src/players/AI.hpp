#ifndef AI_HPP
#define AI_HPP

#include "Player.hpp"

enum AIDifficulty { Vihannes, Retardi, Cheater };

class Match;  //...cpp things

class AI : public Player {
 public:
  AI(const std::string& name, Deck deck, AIDifficulty diff)
      : Player(name, deck), difficulty_(diff) {}

  std::unique_ptr<Move> play(Match& match) override;  // AI Strategy

  void setDifficulty(AIDifficulty diff) { difficulty_ = diff; }
  AIDifficulty getDifficulty() const { return difficulty_; }

 private:
  AIDifficulty difficulty_;
  std::shared_ptr<Card> favoriteCard_ =
      nullptr;  // To have a persistent card choice to play
};

#endif
