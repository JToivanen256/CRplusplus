#include "Match.hpp"

#include <cmath>
#include <cstdint>
#include <iostream>

#include "../entities/DefaultTower.hpp"
#include "../entities/TestUnit.hpp"

Match::Match(Player& player1, Player& player2)
    : player1_(player1), player2_(player2), map_(30, 50) {
  // This is not nice but it will do for now
  switch (player1_.getTowerType()) {
    case TowerType::Default:  // n * tilesize (13), player2 is above on screen
      towers_.emplace_back(
          std::make_unique<DefaultTower>(15 * 13, 45 * 13, true, &player1_));
      towers_.emplace_back(
          std::make_unique<DefaultTower>(6 * 13, 41 * 13, false, &player1_));
      towers_.emplace_back(
          std::make_unique<DefaultTower>(24 * 13, 41 * 13, false, &player1_));
      break;
  }

  switch (player2_.getTowerType()) {
    case TowerType::Default:
      towers_.emplace_back(
          std::make_unique<DefaultTower>(15 * 13, 5 * 13, true, &player2_));
      towers_.emplace_back(
          std::make_unique<DefaultTower>(6 * 13, 9 * 13, false, &player2_));
      towers_.emplace_back(
          std::make_unique<DefaultTower>(24 * 13, 9 * 13, false, &player2_));
      break;
  }
  map_.generateDefaultMap();

  {
    // Register towers as occupants on the grid
    int tileSize = map_.getGrid().getTileSize();
    int maxRows = map_.getGrid().getRows();
    int maxCols = map_.getGrid().getColumns();

    for (const auto& tower : towers_) {
      const sf::FloatRect b = tower->getSprite().getGlobalBounds();
      float left = b.left;
      float top = b.top;
      float right = b.left + b.width - 0.001f;
      float bottom = b.top + b.height - 0.001f;

      // convert world pixels -> grid indices
      int r0 = map_.getGrid().worldToGrid(sf::Vector2f(left, top)).first;
      int c0 = map_.getGrid().worldToGrid(sf::Vector2f(left, top)).second;
      int r1 = map_.getGrid().worldToGrid(sf::Vector2f(right, bottom)).first;
      int c1 = map_.getGrid().worldToGrid(sf::Vector2f(right, bottom)).second;

      // clamp to grid
      r0 = std::max(0, std::min(r0, maxRows - 1));
      r1 = std::max(0, std::min(r1, maxRows - 1));
      c0 = std::max(0, std::min(c0, maxCols - 1));
      c1 = std::max(0, std::min(c1, maxCols - 1));

      // Register occupants
      for (int r = r0; r <= r1; ++r) {
        for (int c = c0; c <= c1; ++c) {
          map_.getGrid().addOccupant(
              r, c, reinterpret_cast<intptr_t>(tower.get()) & 0x7fffffff);
        }
      }

      std::cout << "tower tiles: (" << r0 << "," << c0 << ") -> (" << r1 << ","
                << c1 << ")" << std::endl;
    }
  }

  player1.setColor(sf::Color::Blue);
  player2.setColor(sf::Color::Red);
}

void Match::update(float deltaTime) {
  if (isOver()) {
    return;
  };
  player1_.update(deltaTime);
  player2_.update(deltaTime);

  // Remove dead units and clear their occupants
  units_.erase(
      std::remove_if(units_.begin(), units_.end(),
                     [this](const std::unique_ptr<Unit>& u) {
                       if (!u) return true;
                       if (u->isDead()) {
                         auto position = u->getPosition();
                         auto gp = map_.getGrid().worldToGrid(sf::Vector2f(
                             (float)position.x, (float)position.y));
                         map_.getGrid().removeOccupant(
                             gp.first, gp.second,
                             0);  // remove occupant id unknown; grid
                                  // will handle removal if implemented
                         return true;
                       }
                       return false;
                     }),
      units_.end());

  checkForWinner();
  matchTime_ += deltaTime;

  std::vector<Entity*> entities = allEntities();

  // Update units
  for (auto& unit : units_) {
    if (!unit->isAttacking()) {
      if (unit->targetsOnlyTowers()) {
        entities = allTowerEntities();
      } else {
        entities = allEntities();
      }
      auto target = unit->scanNearestEnemy(entities);
      // If found a target, set it and plan path
      if (target.first) {
        const float replanThreshold = 4.0f;
        if (unit->getTarget() != target.first) {
          unit->setTarget(target.first);
          unit->setLastTargetPoint(target.second);
          auto unitPos = unit->getPosition();
          auto path = map_.findPath(unitPos, target.second);
          if (path.size() >= 2) unit->setPath(path);
        } else {
          // Check if target has moved significantly to replan path
          sf::Vector2f last = unit->getLastTargetPoint();
          float dx = target.second.x - last.x;
          float dy = target.second.y - last.y;
          if ((dx * dx + dy * dy) > (replanThreshold * replanThreshold)) {
            unit->setLastTargetPoint(target.second);
            auto unitPos = unit->getPosition();
            auto path = map_.findPath(unitPos, target.second);
            if (path.size() >= 2) unit->setPath(path);
          }
        }
      } else {  // No target found, go for enemy king tower
        // auto enemyKT = (unit->getOwner() == &player1_) ?
        // getKingTowers().second : getKingTowers().first;

        entities = allTowerEntities();  // all enemy towers
        auto enemyTower = unit->scanNearestTower(entities).first;

        if (enemyTower && unit->getTarget() != enemyTower) {
          std::cout << "No target found, going for enemy king tower\n";
          unit->setTarget(enemyTower);
          auto TargetPos = enemyTower->getPosition();

          // Position just outside tower sprite to avoid occupied tiles
          if (unit->getOwner() == &player1_) {
            TargetPos.y += enemyTower->getSpriteBounds().height / 2 + 1;
          } else {
            TargetPos.y -= enemyTower->getSpriteBounds().height / 2 + 1;
          }
          auto unitPos = unit->getPosition();
          auto path = map_.findPath(unitPos, TargetPos);
          if (path.size() >= 2) {
            unit->setPath(path);
            unit->setLastTargetPoint(TargetPos);
          }
        }
      }
    }
    unit->update(deltaTime);
  }
}

void Match::render(sf::RenderWindow& window) {
  map_.getGrid().draw(window);
  for (const auto& tower : towers_) {
    tower->draw(window);
  }
  // Draw units
  for (const auto& u : units_) {
    if (u && !u->isDead()) {
      u->draw(window);
    }
  }
}

void Match::handleInput(sf::Event event) {
  // Handle match input
}

bool Match::isOver() const { return winner_ != nullptr; }

Player* Match::winner() const { return winner_; }

void Match::checkForWinner() {
  // Check if a player has lost his king tower
  for (const auto& tower : towers_) {
    if (tower->isKingTower() && tower->isDead()) {
      if (tower->getOwner() == &player1_) {
        winner_ = &player2_;
      } else {
        winner_ = &player1_;
      }
    }
  }

  // If time has ended and no winner yet, player who has destroyed more towers
  // wins
  if (matchTime_ >= maxMatchTime_ && winner_ == nullptr) {
    int p1Towers = 0;
    int p1Health = 0;
    int p2Towers = 0;
    int p2Health = 0;

    for (const auto& tower : towers_) {
      if (!tower->isDead()) {
        if (tower->getOwner() == &player1_) {
          p1Towers++;
          p1Health += tower->getHealth();
        } else {
          p2Towers++;
          p2Health += tower->getHealth();
        }
      }
    }
    if (p1Towers > p2Towers) {
      winner_ = &player1_;
    } else if (p2Towers > p1Towers) {
      winner_ = &player2_;
    } else {  // If towers are even then check health
      if (p1Health >= p2Health) {
        winner_ = &player1_;
      } else {
        winner_ = &player2_;
      }
    }
  }
}

float Match::getRemainingTime() const {
  return std::max(0.0f, maxMatchTime_ - matchTime_);
}

Map& Match::getMap() { return map_; }

const Map& Match::getMap() const { return map_; }

std::vector<std::unique_ptr<Unit>>& Match::getUnits() { return units_; }

const std::vector<std::unique_ptr<Tower>>& Match::getTowers() const {
  return towers_;
}

void Match::addUnit(std::unique_ptr<Unit> unit) {
  units_.emplace_back(std::move(unit));
}

/**
 * Instead of having separate classes inheriting from Unit have all the
 * information for each unit type stored with the card including the
 * sprite for the unit
 */
void Match::createUnitFromCard(const UnitCard& card, int gridX, int gridY,
                               Player& owner) {
  int tileSize = map_.getGrid().getTileSize();
  float worldX = gridX * tileSize + tileSize / 2;
  float worldY = gridY * tileSize + tileSize / 2;

  auto unit = std::make_unique<TestUnit>(
      worldX, worldY, card.getHealth(), card.getDamage(),
      card.getAttackCooldown(), card.getAttackRange(), card.getMovementSpeed(),
      card.getVisionRange(), &owner, card.getName(), card.isBuildingTargeter());

  {
    std::string spritePath = "assets/sprites/" + card.getSpritePath();
    auto tex = std::make_shared<sf::Texture>();
    if (tex->loadFromFile(spritePath)) {
      unit->setTextureShared(tex);

      int tileSize = map_.getGrid().getTileSize();
      float desiredPx = tileSize * 1.5f;
      auto ts = tex->getSize();
      if (ts.x > 0 && ts.y > 0) {
        unit->getSprite().setScale(desiredPx / static_cast<float>(ts.x),
                                   desiredPx / static_cast<float>(ts.y));
      }
    } else {
      std::cerr << "Failed to load texture: " << spritePath << "\n";
    }
  }

  unit->syncVisual();
  addUnit(std::move(unit));

  for (const auto& unit : units_) {
    sf::Vector2f gp = unit->getPosition();
    std::string cardName = unit->getName();
    std::cout << cardName << " at (" << gp.x << ", " << gp.y << ")\n";
  }
}

std::vector<Entity*> Match::allEntities() {
  std::vector<Entity*> entities;
  for (const auto& unit : units_) {
    entities.push_back(unit.get());
  }
  for (const auto& building : buildings_) {
    entities.push_back(building.get());
  }
  for (const auto& tower : towers_) {
    entities.push_back(tower.get());
  }
  return entities;
}

std::pair<Tower*, Tower*> Match::getKingTowers() const {
  Tower* k1 = nullptr;
  Tower* k2 = nullptr;
  for (const auto& tptr : towers_) {
    if (!tptr) continue;
    Tower* t = tptr.get();
    if (!t->isKingTower()) continue;
    if (t->getOwner() == &player1_)
      k1 = t;
    else if (t->getOwner() == &player2_)
      k2 = t;
  }
  return {k1, k2};
}

std::vector<Entity*> Match::allTowerEntities() {
  std::vector<Entity*> entities;
  for (const auto& tower : towers_) {
    entities.push_back(tower.get());
  }
  return entities;
}