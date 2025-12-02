#ifndef MATCHSTATE_HPP
#define MATCHSTATE_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <vector>

#include "../game/Match.hpp"
#include "../players/Player.hpp"
#include "../players/SpellCard.hpp"
#include "CardRenderer.hpp"
#include "GameState.hpp"

class MatchState : public GameState {
 private:
  struct SpellFlight {
    std::shared_ptr<SpellCard> card;
    sf::Vector2f start;
    sf::Vector2f target;
    float duration = 1.3f;
    float elapsed = 0.f;
    bool impactTriggered = false;
  };

  struct SpellImpact {
    sf::Vector2f position;
    float radius = 0.f;
    float lifetime = 0.45f;
    float elapsed = 0.f;
  };

  Match match_;
  Player& player1_;
  Player& player2_;
  sf::Font font_;
  CardRenderer cardRenderer_;
  int selectedCardIndex_ = -1;
  const float cardScale_ = 40.f;
  const float cardH_ = 40.f;
  const float cardGap_ = 45.f;
  const float cardStartX_ = 28.f;
  const float cardY_ = 655.f;
  const float highlightScale_ = 1.05f;

  bool handleCardClick(sf::Vector2f mousePos);
  void handleGridClick(sf::Vector2f mousePos);
  bool isValidSpawnPosition(int row, int col) const;
  bool isValidSpellTarget(int row, int col) const;
  void spawnUnit(int row, int col, const std::shared_ptr<Card>& cardPtr);
  void castSpell(int row, int col, const std::shared_ptr<SpellCard>& card);
  void updateSpellAnimations(float deltaTime);
  void renderSpellAnimations(sf::RenderWindow& window);
  void applySpellDamage(const SpellCard& card, const sf::Vector2f& center);

  std::vector<SpellFlight> activeSpellFlights_;
  std::vector<SpellImpact> activeSpellImpacts_;

 public:
  MatchState(Player& p1, Player& p2, AIDifficulty difficulty);
  void update(float deltaTime) override;
  void handleInput(sf::RenderWindow& window, sf::Event event) override;
  void render(sf::RenderWindow& window) override;
  std::string getWinnerName() const;
  bool matchOver_ = false;
};

#endif