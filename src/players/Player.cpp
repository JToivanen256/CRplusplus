#include "Player.hpp"

Player::Player(const std::string& name, Deck deck)
    : name_(name), deck_(deck), elixir_(0), hand_(deck.initializeHand()) {}

void Player::update(float deltaTime) {
  elixirTimer_ += deltaTime * elixirRegenRate_;
  while (elixirTimer_ >= 1.0f) {
    if (elixir_ < 10) {
      elixir_++;
    }
    elixirTimer_ = 0.0f;
  }
}

int Player::getElixir() const { return elixir_; }

const Hand& Player::getHand() const { return hand_; }

const std::string& Player::getName() const { return name_; }

const TowerType& Player::getTowerType() const { return towerType_; }