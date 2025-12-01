#include "MatchState.hpp"

#include <algorithm>
#include <iostream>
#include <string>

#include "../entities/TestUnit.hpp"
#include "../players/UnitCard.hpp"
#include "CardRenderer.hpp"

MatchState::MatchState(Player& p1, Player& p2)
    : player1_(p1), player2_(p2), match_(p1, p2) {
  if (!font_.loadFromFile("assets/fonts/MomoTrustDisplay-Regular.ttf")) {
    std::cerr << "Failed to load font!" << std::endl;
  }
}

void MatchState::update(float deltaTime) {
  match_.update(deltaTime);
  updateSpellAnimations(deltaTime);
  if (match_.isOver()) {
    matchOver_ = true;
  }
}

void MatchState::handleInput(sf::RenderWindow& window, sf::Event event) {
  if (event.type == sf::Event::MouseButtonPressed &&
      event.mouseButton.button == sf::Mouse::Left) {
    sf::Vector2f mousePos =
        window.mapPixelToCoords(sf::Mouse::getPosition(window));

    bool clickedCard = handleCardClick(mousePos);

    if (!clickedCard && selectedCardIndex_ != -1) {
      handleGridClick(mousePos);
    }
  }
}

void MatchState::render(sf::RenderWindow& window) {
  match_.render(window);

  sf::Text elixir(std::to_string(player1_.getElixir()), font_, 30);
  elixir.setPosition(187, 735);
  elixir.setFillColor(sf::Color::White);
  window.draw(elixir);

  const auto& cards = player1_.getHand().getCards();

  for (size_t i = 0; i < cards.size(); ++i) {
    const auto& card = cards[i];
    float x = cardStartX_ + i * (cardScale_ + cardGap_);

    float scale = (selectedCardIndex_ == static_cast<int>(i))
                      ? cardScale_ / 256.f * highlightScale_
                      : cardScale_ / 256.f;
    float yPos = (selectedCardIndex_ == static_cast<int>(i))
                     ? cardY_ - (cardH_ * (highlightScale_ - 1.0f) / 2.0f)
                     : cardY_;

    cardRenderer_.renderCard(*card, window, {x, yPos}, {scale, scale}, font_);
  }

  float remainingTime = match_.getRemainingTime();
  int secs = static_cast<int>(remainingTime + 0.5f);
  int minutes = secs / 60;
  int seconds = secs % 60;

  std::string timeStr = std::to_string(minutes) + ":" +
                        (seconds < 10 ? "0" : "") + std::to_string(seconds);

  sf::Text time(timeStr, font_, 30);
  time.setPosition(10, 10);
  time.setFillColor(sf::Color::White);
  window.draw(time);

  renderSpellAnimations(window);
}

std::string MatchState::getWinnerName() const {
  Player* winner = match_.winner();
  if (winner) {
    return winner->getName();
  } else {
    return "No winner wtf";
  }
}

bool MatchState::handleCardClick(sf::Vector2f mousePos) {
  const auto& cards = player1_.getHand().getCards();

  for (size_t i = 0; i < cards.size(); ++i) {
    float x = cardStartX_ + i * (cardScale_ + cardGap_);
    float y = cardY_;

    if (mousePos.x >= x && mousePos.x <= x + cardScale_ * 2 &&
        mousePos.y >= y && mousePos.y <= y + cardH_ * 2) {
      selectedCardIndex_ = (selectedCardIndex_ == static_cast<int>(i)) ? -1
                                                                      : static_cast<int>(i);
      return true;
    }
  }

  return false;
}

void MatchState::handleGridClick(sf::Vector2f mousePos) {
  auto [row, col] = match_.getMap().getGrid().worldToGrid(mousePos);

  if (!match_.getMap().getGrid().inBounds(row, col)) {
    return;
  }

  const auto& cards = player1_.getHand().getCards();
  if (selectedCardIndex_ < 0 || selectedCardIndex_ >= static_cast<int>(cards.size())) {
    return;
  }

  auto cardPtr = cards[selectedCardIndex_];
  auto unitCard = std::dynamic_pointer_cast<UnitCard>(cardPtr);
  auto spellCard = std::dynamic_pointer_cast<SpellCard>(cardPtr);

  if (unitCard) {
    if (!isValidSpawnPosition(row, col)) {
      std::cout << "Invalid spawn position!" << std::endl;
      return;
    }
  } else if (spellCard) {
    if (!isValidSpellTarget(row, col)) {
      std::cout << "Invalid spell target!" << std::endl;
      return;
    }
  } else {
    std::cout << "Unsupported card type!" << std::endl;
    return;
  }

  if (player1_.playCard(cardPtr)) {
    if (unitCard) {
      spawnUnit(row, col, cardPtr);
    } else if (spellCard) {
      castSpell(row, col, spellCard);
    }
  }

  selectedCardIndex_ = -1;
}

bool MatchState::isValidSpawnPosition(int row, int col) const {
  const auto& grid = match_.getMap().getGrid();

  if (grid.isOccupied(row, col)) {
    return false;
  }

  int gridRows = grid.getRows();
  int midpoint = gridRows / 2;
  if (row < midpoint + 2) {
    return false;
  }

  if (!grid.at(row, col).walkable) {
    return false;
  }

  return true;
}

bool MatchState::isValidSpellTarget(int row, int col) const {
  const auto& grid = match_.getMap().getGrid();
  int gridRows = grid.getRows();
  int midpoint = gridRows / 2;

  if (row >= midpoint - 2) {
    return false;
  }

  if (!grid.at(row, col).walkable) {
    return false;
  }

  return true;
}

void MatchState::spawnUnit(int row, int col, const std::shared_ptr<Card>& cardPtr) {
  if (!cardPtr) {
    std::cerr << "Invalid card pointer!" << std::endl;
    return;
  }

  if (auto ucard = std::dynamic_pointer_cast<UnitCard>(cardPtr)) {
    match_.createUnitFromCard(*ucard, col, row, player1_);
  }

  int unitId = static_cast<int>(row * 100 + col);

  std::cout << "Spawned unit for card '" << cardPtr->getName() << "' at grid ("
            << row << ", " << col << ")" << std::endl;

  for (const auto& unit : match_.getUnits()) {
    sf::Vector2f pos = unit->getPosition();
    std::string cardName = unit->getName();
    std::cout << cardName << " at grid (" << pos.x << ", " << pos.y << ")\n";
  }
}

void MatchState::castSpell(int row, int col, const std::shared_ptr<SpellCard>& card) {
  if (!card) {
    return;
  }

  const auto& grid = match_.getMap().getGrid();
  sf::Vector2f target = grid.gridToWorldCenter(row, col);

  int rows = grid.getRows();
  int cols = grid.getColumns();
  sf::Vector2f start = grid.gridToWorldCenter(rows - 2, cols / 2);

  SpellFlight flight;
  flight.card = card;
  flight.start = start;
  flight.target = target;
  activeSpellFlights_.push_back(flight);
}

void MatchState::applySpellDamage(const SpellCard& card, const sf::Vector2f& center) {
  const float tileSize = static_cast<float>(match_.getMap().getGrid().getTileSize());
  const float radiusPx = static_cast<float>(card.getRadius()) * tileSize;
  const float radiusSq = radiusPx * radiusPx;

  auto applySplash = [&](Entity& entity) {
    sf::Vector2f diff = entity.getPosition() - center;
    float distSq = diff.x * diff.x + diff.y * diff.y;
    if (distSq <= radiusSq) {
      entity.takeDamage(card.getDamage());
    }
  };

  for (auto& unit : match_.getUnits()) {
    if (unit && !unit->isDead()) {
      applySplash(*unit);
    }
  }

  for (const auto& tower : match_.getTowers()) {
    if (tower && !tower->isDead()) {
      applySplash(*tower);
    }
  }
}

void MatchState::updateSpellAnimations(float deltaTime) {
  const float tileSize = static_cast<float>(match_.getMap().getGrid().getTileSize());

  for (auto& flight : activeSpellFlights_) {
    flight.elapsed += deltaTime;
    if (!flight.impactTriggered && flight.elapsed >= flight.duration) {
      flight.impactTriggered = true;

      SpellImpact impact;
      impact.position = flight.target;
      impact.radius = static_cast<float>(flight.card->getRadius()) * tileSize;
      activeSpellImpacts_.push_back(impact);

      applySpellDamage(*flight.card, flight.target);
    }
  }

  activeSpellFlights_.erase(
      std::remove_if(activeSpellFlights_.begin(), activeSpellFlights_.end(),
                     [](const SpellFlight& f) {
                       return f.elapsed >= f.duration + 0.1f;
                     }),
      activeSpellFlights_.end());

  for (auto& impact : activeSpellImpacts_) {
    impact.elapsed += deltaTime;
  }

  activeSpellImpacts_.erase(
      std::remove_if(activeSpellImpacts_.begin(), activeSpellImpacts_.end(),
                     [](const SpellImpact& i) {
                       return i.elapsed >= i.lifetime;
                     }),
      activeSpellImpacts_.end());
}

void MatchState::renderSpellAnimations(sf::RenderWindow& window) {
  for (const auto& flight : activeSpellFlights_) {
    float t = std::clamp(flight.elapsed / flight.duration, 0.f, 1.f);
    sf::Vector2f pos = flight.start + (flight.target - flight.start) * t;

    sf::CircleShape projectile(6.f);
    projectile.setOrigin(6.f, 6.f);
    projectile.setFillColor(sf::Color(255, 200, 50));
    projectile.setOutlineColor(sf::Color::Black);
    projectile.setOutlineThickness(1.f);
    projectile.setPosition(pos);
    window.draw(projectile);
  }

  for (const auto& impact : activeSpellImpacts_) {
    float alpha = 1.f - std::clamp(impact.elapsed / impact.lifetime, 0.f, 1.f);
    sf::CircleShape ring(impact.radius);
    ring.setOrigin(impact.radius, impact.radius);
    ring.setPosition(impact.position);
    ring.setFillColor(sf::Color(255, 120, 0, static_cast<sf::Uint8>(40 * alpha)));
    ring.setOutlineColor(sf::Color(255, 255, 0, static_cast<sf::Uint8>(200 * alpha)));
    ring.setOutlineThickness(2.f);
    window.draw(ring);
  }
}