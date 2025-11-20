#include "Match.hpp"
#include "../entities/DefaultTower.cpp"

Match::Match(Player& player1, Player& player2)
  : player1_(player1), player2_(player2), map_(30, 50) {
    towers_.emplace_back(std::make_unique<DefaultTower>(169, 39, 13, 3, 1000, 50, 1.5f, 100.0f, 4, true, &player1_));
    towers_.emplace_back(std::make_unique<DefaultTower>(169, 559, 13, 43, 1000, 50, 1.5f, 100.0f, 4, true, &player2_));
    map_.generateDefaultMap();
  }


void Match::update(float deltaTime) {
  if (isOver()) { return; };
  player1_.update(deltaTime);
  player2_.update(deltaTime);

  checkForWinner();
  matchTime_ += deltaTime;
}

void Match::render(sf::RenderWindow& window) {
  map_.getGrid().draw(window);
  for (const auto& tower : towers_) {
    tower->draw(window);
  }
}

void Match::handleInput(sf::Event event) {
  // Handle match input
}

bool Match::isOver() const {
  return winner_ != nullptr;
}

Player* Match::winner() const {
  return winner_;
}

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

  // If time has ended and no winner yet, player who has destroyed more towers wins
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
    } else { // If towers are even then check health
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