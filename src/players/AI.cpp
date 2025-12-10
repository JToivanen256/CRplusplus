#include "AI.hpp"

#include <algorithm>
#include <cmath>
#include <random>

#include "../entities/Unit.hpp"
#include "../game/Match.hpp"
#include "SpellCard.hpp"
#include "UnitCard.hpp"

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

    // Prefers the obviously op Dick Rider, else looks for enemy clusters to
    // spell taking into account their speed, else begins to build pushes by
    // playing slow cards from the back or into the same cluster and fast ones
    // from the bridge once the slow ones get there. If there are enemies,
    // defend on that side
    case Cheater: {
      const auto& hand = this->getHand().getCards();
      if (hand.empty()) break;

      const auto& grid = match.getMap().getGrid();
      int rows = grid.getRows();
      int cols = grid.getColumns();

      for (auto c : hand) {
        if (c->getName() == "Dick Rider") {
          favoriteCard_ = c;
          break;
        }
      }

      // Determine which side AI's towers are on (average tower row)
      int aiTowerRowSum = 0;
      int aiTowerCount = 0;
      for (const auto& t : match.getTowers()) {
        if (t->getOwner() == this) {
          auto pos = t->getSprite().getPosition();
          auto [r, c] = grid.worldToGrid(pos);
          aiTowerRowSum += r;
          aiTowerCount++;
        }
      }
      int aiTowerAvgRow =
          aiTowerCount ? aiTowerRowSum / aiTowerCount : (rows / 2);

      // compute enemy counts and preferred side based on that
      int enemyLeftCount = 0, enemyRightCount = 0;
      for (const auto& u : match.getUnits()) {
        if (!u) continue;
        if (u->getOwner() == this) continue;  // only enemies
        auto [r, c] = grid.worldToGrid(u->getPosition());
        if (c < cols / 2)
          enemyLeftCount++;
        else
          enemyRightCount++;
      }

      auto computePreferredSideCol = [&]() {
        if (enemyLeftCount > enemyRightCount) return cols / 4;
        if (enemyRightCount > enemyLeftCount) return (cols * 3) / 4;
        return cols / 2;  // tie -> center
      };

      int preferredSideCol = computePreferredSideCol();

      // If we already have a persistent favorite, prefer it and wait for it to
      // be playable.
      if (favoriteCard_) {
        // Check that favorite is still in hand
        if (std::find(hand.begin(), hand.end(), favoriteCard_) != hand.end()) {
          if (this->getElixir() >= favoriteCard_->getCost()) {
            // Play favorite immediately. Only Dick Rider can be favorite here
            // so just place it accordingly
            int targetRow = (aiTowerAvgRow < rows / 2) ? 1 : (rows - 2);
            int targetCol = preferredSideCol;
            return std::make_unique<Move>(
                Move{targetRow, targetCol, favoriteCard_});
          } else
            return nullptr;  // No elixir
        } else {
          // Favorite not in hand anymore, clear it
          favoriteCard_.reset();
        }
      }

      // Find enemy clusters
      std::vector<Unit*> enemies;
      for (const auto& u : match.getUnits()) {
        if (!u) continue;
        if (u->getOwner() == this) continue;
        enemies.push_back(u.get());
      }

      auto gridDist = [&grid](const sf::Vector2f& posA,
                              const sf::Vector2f& posB) {
        auto [rowA, colA] = grid.worldToGrid(posA);
        auto [rowB, colB] = grid.worldToGrid(posB);
        int dx = colA - colB;
        int dy = rowA - rowB;
        return std::max(std::abs(dx), std::abs(dy));
      };

      std::vector<bool> visited(enemies.size(), false);
      std::vector<std::vector<int>> clusters;
      for (size_t i = 0; i < enemies.size(); ++i) {
        if (visited[i]) continue;
        std::vector<int> stack = {(int)i};
        std::vector<int> cluster;
        visited[i] = true;
        while (!stack.empty()) {
          int idx = stack.back();
          stack.pop_back();
          cluster.push_back(idx);
          for (size_t j = 0; j < enemies.size(); ++j) {
            if (visited[j]) continue;
            if (gridDist(enemies[idx]->getPosition(),
                         enemies[j]->getPosition()) <= 3) {
              visited[j] = true;
              stack.push_back((int)j);
            }
          }
        }
        clusters.push_back(cluster);
      }

      // Choose the biggest (and filter out sizes < 3)
      int bestClusterIdx = -1;
      size_t bestSize = 0;
      for (size_t i = 0; i < clusters.size(); ++i) {
        if (clusters[i].size() >= 3 && clusters[i].size() > bestSize) {
          bestSize = clusters[i].size();
          bestClusterIdx = (int)i;
        }
      }

      auto findFirstSpell = [&]() -> std::shared_ptr<Card> {
        for (const auto& cptr : hand) {
          if (!cptr) continue;
          if (std::dynamic_pointer_cast<SpellCard>(cptr)) return cptr;
        }
        return nullptr;
      };

      if (bestClusterIdx != -1) {
        auto spellCard = findFirstSpell();

        if (spellCard && this->getElixir() >= spellCard->getCost()) {
          float sumR = 0.f;
          float sumC = 0.f;
          bool anyAttacking = false;
          for (int idx : clusters[bestClusterIdx]) {
            auto [r, c] = grid.worldToGrid(enemies[idx]->getPosition());
            sumR += static_cast<float>(r);
            sumC += static_cast<float>(c);
            if (enemies[idx]->isAttacking()) {
              anyAttacking = true;
            }
          }
          float centR = sumR / clusters[bestClusterIdx].size();
          float centC = sumC / clusters[bestClusterIdx].size();

          int targetRow;
          // Keep row logic based on centroid / prediction, but force column
          // to the preferred enemy side so spells prioritize that side.
          if (anyAttacking) {
            targetRow = static_cast<int>(std::round(centR));
          } else {
            int dir = (aiTowerAvgRow < centR) ? -1 : 1;
            targetRow = static_cast<int>(std::round(centR)) + dir * 3;
          }

          int targetCol = static_cast<int>(std::round(centC));

          // Clamp to board bounds
          if (targetRow < 0) targetRow = 0;
          if (targetRow >= rows) targetRow = rows - 1;
          if (targetCol < 0) targetCol = 0;
          if (targetCol >= cols) targetCol = cols - 1;

          return std::make_unique<Move>(Move{targetRow, targetCol, spellCard});
        }
      }

      // Otherwise build a push. If own units are near river, play fast units
      // to stack; otherwise play slow units from back or behind existing ones.
      // If there are enemy units, prefer their side instead and defend.
      int riverRow = rows / 2;
      bool ownNearRiver = false;
      int ownColNearRiver = cols / 2;
      for (const auto& u : match.getUnits()) {
        if (!u) continue;
        if (u->getOwner() != this) continue;
        auto [r, c] = grid.worldToGrid(u->getPosition());
        if (std::abs(r - riverRow) <= 3) {
          ownNearRiver = true;
          ownColNearRiver = c;
          break;
        }
      }

      std::shared_ptr<Card> slowPick = nullptr;
      float bestSlow = 1e9f;
      std::shared_ptr<Card> fastPick = nullptr;
      float bestFast = -1.f;
      for (const auto& cptr : hand) {
        if (!cptr) continue;
        if (auto uc = std::dynamic_pointer_cast<UnitCard>(cptr)) {
          float spd = uc->getMovementSpeed();
          if (spd < bestSlow) {
            bestSlow = spd;
            slowPick = cptr;
          }
          if (spd > bestFast) {
            bestFast = spd;
            fastPick = cptr;
          }
        }
      }

      // 2 options now: fast and slow
      if (ownNearRiver && fastPick &&
          this->getElixir() >= fastPick->getCost()) {
        int targetRow =
            (aiTowerAvgRow < rows / 2) ? riverRow - 4 : riverRow + 4;
        return std::make_unique<Move>(
            Move{targetRow, ownColNearRiver, fastPick});
      }

      if (slowPick && this->getElixir() >= slowPick->getCost()) {
        // Try to play 1 tile back from an existing slow unit, if that location
        // is invalid, just wait and play later
        int slowTargetRow = (aiTowerAvgRow < rows / 2) ? 1 : (rows - 2);
        int slowTargetCol = preferredSideCol;

        bool foundSlowUnit = false;
        bool placedBehind = false;
        if (auto uc = std::dynamic_pointer_cast<UnitCard>(slowPick)) {
          float slowSpeed = uc->getMovementSpeed();
          // Only attempt behind-placement when enemy counts are equal (or
          // none). If enemies are present and unequal, prefer the enemy side
          // instead.
          if (enemyLeftCount == enemyRightCount) {
            // search our units for a slow one
            for (const auto& u : match.getUnits()) {
              if (!u) continue;
              if (u->getOwner() != this) continue;
              if (u->getMovementSpeed() <= slowSpeed + 1e-6f) {
                foundSlowUnit = true;
                auto [ur, uccol] = grid.worldToGrid(u->getPosition());
                int behindRow = ur + ((aiTowerAvgRow < rows / 2) ? -1 : 1);
                // check bounds and walkability/occupancy
                if (grid.inBounds(behindRow, uccol) &&
                    grid.at(behindRow, uccol).walkable &&
                    !grid.isOccupied(behindRow, uccol)) {
                  slowTargetRow = behindRow;
                  slowTargetCol = uccol;
                  placedBehind = true;
                  break;
                } else {
                  // no valid spot behind this unit - wait
                  return nullptr;
                }
              }
            }
          }
        }

        // If we didn't find any existing slow unit, fall back to default
        // back-row placement.
        return std::make_unique<Move>(
            Move{slowTargetRow, slowTargetCol, slowPick});
      }
    } break;
  }
  return nullptr;  // No move this time
}
