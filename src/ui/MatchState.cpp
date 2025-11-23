#include "MatchState.hpp"

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
  if (match_.isOver()) {
    matchOver_ = true;
  }
}

void MatchState::handleInput(sf::RenderWindow& window, sf::Event event) {
  if (event.type == sf::Event::MouseButtonPressed &&
      event.mouseButton.button == sf::Mouse::Left) {
    sf::Vector2f mousePos =
        window.mapPixelToCoords(sf::Mouse::getPosition(window));

    // First check if clicking on a card
    bool clickedCard = handleCardClick(mousePos);

    // If the click didn't hit a card but we have a selected card, check grid
    if (!clickedCard && selectedCardIndex_ != -1) {
      handleGridClick(mousePos);
    }
  }
}

void MatchState::render(sf::RenderWindow& window) {
  match_.render(window);
  // Draw Elixir bar and hand here
  sf::Text elixir(std::to_string(player1_.getElixir()), font_, 30);
  elixir.setPosition(187, 735);
  elixir.setFillColor(sf::Color::White);
  window.draw(elixir);

  // Units are rendered by Match::render (which draws match_.units_) TODO:
  // implement unit drawing in Unit class

  // Draw player1's hand using CardRenderer
  const auto& cards = player1_.getHand().getCards();

  for (size_t i = 0; i < cards.size(); ++i) {
    const auto& card = cards[i];
    float x = cardStartX_ + i * (cardScale_ + cardGap_);

    // Use highlight scale for selected card
    float scale = (selectedCardIndex_ == (int)i)
                      ? cardScale_ / 256.f * highlightScale_
                      : cardScale_ / 256.f;
    float yPos = (selectedCardIndex_ == (int)i)
                     ? cardY_ - (cardH_ * (highlightScale_ - 1.0f) / 2.0f)
                     : cardY_;

    cardRenderer_.renderCard(card, window, {x, yPos}, {scale, scale}, font_);
  }
  std::vector<std::unique_ptr<Unit>>& units = match_.getUnits();
  for (const auto& unit : units) {
    unit->draw(window);
  }

  // Show remaining time in the match by getting the info from Match
  float remainingTime = match_.getRemainingTime();
  int secs = static_cast<int>(remainingTime + 0.5f);
  int minutes = secs / 60;
  int seconds = secs % 60;
  // Time format
  std::string timeStr = std::to_string(minutes) + ":" +
                        (seconds < 10 ? "0" : "") + std::to_string(seconds);

  sf::Text time(timeStr, font_, 30);
  time.setPosition(10, 10);
  time.setFillColor(sf::Color::White);
  window.draw(time);
}

std::string MatchState::getWinnerName() const {
  Player* winner = match_.winner();
  if (winner) {
    return winner->getName();
  } else {
    // Shouldn't be possible
    return "No winner wtf";
  }
}

bool MatchState::handleCardClick(sf::Vector2f mousePos) {
  const auto& cards = player1_.getHand().getCards();

  for (size_t i = 0; i < cards.size(); ++i) {
    float x = cardStartX_ + i * (cardScale_ + cardGap_);
    float y = cardY_;

    // Check if click is within card bounds
    if (mousePos.x >= x && mousePos.x <= x + cardScale_ * 2 &&
        mousePos.y >= y && mousePos.y <= y + cardH_ * 2) {
      // Toggle selection
      selectedCardIndex_ = (selectedCardIndex_ == (int)i) ? -1 : (int)i;
      return true;
    }
  }

  // Click outside cards - do not deselect here so grid clicks can act on
  // the current selection. Return false to indicate no card was clicked.
  return false;
}

void MatchState::handleGridClick(sf::Vector2f mousePos) {
  // Convert world coordinates to grid coordinates
  auto [row, col] = match_.getMap().getGrid().worldToGrid(mousePos);

  if (!match_.getMap().getGrid().inBounds(row, col)) {
    return;
  }

  if (!isValidSpawnPosition(row, col)) {
    std::cout << "Invalid spawn position!" << std::endl;
    return;
  }

  // Get the selected card
  const auto& cards = player1_.getHand().getCards();
  if (selectedCardIndex_ < 0 || selectedCardIndex_ >= (int)cards.size()) {
    return;
  }

  // Make a copy of the card before removing it
  Card selectedCard = cards[selectedCardIndex_];

  // Play card if elixir is sufficient
  if (player1_.playCard(selectedCard)) {
    spawnUnit(row, col, selectedCard);
  }

  // Deselect card
  selectedCardIndex_ = -1;
}

bool MatchState::isValidSpawnPosition(int row, int col) const {
  const auto& grid = match_.getMap().getGrid();

  // Check if occupied (towers are registered as occupants)
  if (grid.isOccupied(row, col)) {
    return false;
  }

  // Check if on player1's side (lower half)
  int gridRows = grid.getRows();
  int midpoint = gridRows / 2;
  if (row < midpoint + 2) {
    return false;
  }

  // Check if walkable (excludes water tiles)
  if (!grid.at(row, col).walkable) {
    return false;
  }

  return true;
}

void MatchState::spawnUnit(int row, int col, const Card& card) {
  std::cout << card.isSpell() << std::endl;
  if (!1) {  // if unitCard get sliced to Card this whole functionality crumbles
             // ffs
    // Use createUnitFromCard to spawn a unit that represents the card
    // match_.createUnitFromCard(card, col, row, player1_);
  } else {
    // Fallback for non-unit cards (spell behavior TODO)
    auto unit = std::make_unique<TestUnit>(
        static_cast<int>(
            match_.getMap().getGrid().gridToWorldCenter(row, col).x),
        static_cast<int>(
            match_.getMap().getGrid().gridToWorldCenter(row, col).y),
        col, row, &player1_);
    match_.addUnit(std::move(unit));
  }

  // Register occupancy with a simple id
  int unitId =
      static_cast<int>(row * 100 + col);  // Simple unique id based on position
  match_.getMap().getGrid().addOccupant(row, col, unitId);

  // Debug prints
  std::cout << "Spawned unit for card '" << card.getName() << "' at grid ("
            << row << ", " << col << ")" << std::endl;

  for (const auto& unit : match_.getUnits()) {
    GridPos gp = unit->getGridPosition();
    std::string cardName = unit->getName();
    std::cout << cardName << " at grid (" << gp.x << ", " << gp.y << ")\n";
  }
}