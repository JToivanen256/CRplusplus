#include "AI.hpp"

#include <random>

#include "../game/Match.hpp"

// Returns a move containing card and position based on match and own
// situation basically, and nullptr if no move is made
std::unique_ptr<Move> AI::play(Match& match) {
  switch (difficulty_) {
    // Play cheapest units in hand from the back or spell-nuke king tower...test
    // difficulty basically
    case Vihannes:
      for (const auto& card : this->getHand().getCards()) {
        if (this->getElixir() >= card->getCost()) {
          if (!card->isSpell()) {
            int col = match.getMap().getGrid().getColumns() / 2;
            int row = 0;
            return std::make_unique<Move>(Move{row, col, card});
          } else if (card->isSpell()) {
            int col = match.getMap().getGrid().getColumns() / 2 - 1;
            int row = match.getMap().getGrid().getRows() - 5;
            return std::make_unique<Move>(Move{row, col, card});
          }
        }
      }
      break;

    // Pre-chooses a favorite card from hand, waits for enough elixir (and + 1,
    // he's slow) and then places it to a random valid spot, depending on card
    // type
    case Retardi: {
      const auto& hand = this->getHand().getCards();
      if (hand.empty()) {
        break;
      }

      std::mt19937 rng(std::random_device{}());
      std::uniform_int_distribution<> cardDist(0, hand.size() - 1);

      if (!favoriteCard_ ||
          std::find(hand.begin(), hand.end(), favoriteCard_) == hand.end()) {
        // Pick new favorite if none or if previous gets played
        favoriteCard_ = hand[cardDist(rng)];
      }

      if (this->getElixir() < favoriteCard_->getCost() + 1) {
        break;  // No elixir
      }

      // Determine placement based on card type
      int row, col;
      const auto& grid = match.getMap().getGrid();

      if (favoriteCard_->isSpell()) {
        // Spells go literally anywhere
        std::uniform_int_distribution<> rowDist(0, grid.getRows() - 1);
        std::uniform_int_distribution<> colDist(0, grid.getColumns() - 1);
        row = rowDist(rng);
        col = colDist(rng);
      } else {
        // Units go to valid locations but still randomly
        std::uniform_int_distribution<> rowDist(0, 22);
        std::uniform_int_distribution<> colDist(0, grid.getColumns() - 1);

        std::vector<std::pair<int, int>> towerCenters = {
            {13, 3}, {3, 5}, {23, 5}};
        bool validSpot = false;
        int attempts = 0;

        // Easier to just spam attempts because towers are in inconvenient spots
        while (!validSpot && attempts < 20) {
          row = rowDist(rng);
          col = colDist(rng);
          attempts++;

          // Check if this spot is in a 4x4 area around a tower
          bool inTowerZone = false;
          for (const auto& [tCol, tRow] : towerCenters) {
            int minCol = tCol - 2;
            int maxCol = tCol + 1;
            int minRow = tRow - 2;
            int maxRow = tRow + 1;

            if (col >= minCol && col <= maxCol && row >= minRow &&
                row <= maxRow) {
              inTowerZone = true;
              break;
            }
          }

          if (!inTowerZone) {
            validSpot = true;
          }
        }

        if (!validSpot) {
          break;  // Couldn't find a valid spot after retries
        }
      }

      return std::make_unique<Move>(Move{row, col, favoriteCard_});
    } break;

    case Cheater:  // TODO
      break;
  }
  return nullptr;  // No move this time
}