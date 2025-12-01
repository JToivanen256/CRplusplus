#ifndef MATCHSTATE_HPP
#define MATCHSTATE_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#include "../game/Match.hpp"
#include "../players/Player.hpp"
#include "CardRenderer.hpp"
#include "GameState.hpp"

class MatchState : public GameState {
 private:
  Match match_;
  Player& player1_;
  Player& player2_;
  sf::Font font_;
  CardRenderer cardRenderer_;
  int selectedCardIndex_ = -1;  // -1 means no card selected
  const float cardScale_ = 40.f;
  const float cardH_ = 40.f;
  const float cardGap_ = 45.f;
  const float cardStartX_ = 28.f;
  const float cardY_ = 655.f;
  const float highlightScale_ = 1.05f;  // Scale multiplier for selected card

  // Returns true if the mouse click hit a card
  bool handleCardClick(sf::Vector2f mousePos);
  void handleGridClick(sf::Vector2f mousePos);
  bool isValidSpawnPosition(int row, int col) const;
  void spawnUnit(int row, int col, const std::shared_ptr<Card>& cardPtr);

 public:
  MatchState(Player& p1, Player& p2, AIDifficulty difficulty);
  virtual void update(float deltaTime) override;
  virtual void handleInput(sf::RenderWindow& window, sf::Event event) override;
  virtual void render(sf::RenderWindow& window) override;
  std::string getWinnerName() const;
  bool matchOver_ = false;
};

#endif
