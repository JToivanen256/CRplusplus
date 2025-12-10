#include "Player.hpp"

#include <iostream>

Player::Player(const std::string& name, Deck deck)
    : name_(name), deck_(deck), elixir_(0), hand_(deck.initializedHand()) {}

void Player::update(float deltaTime) {
  elixirTimer_ += deltaTime * elixirRegenRate_;
  while (elixirTimer_ >= 1.0f) {
    if (elixir_ < 10) {
      elixir_++;
    }
    elixirTimer_ -= 1.0f;
  }
}

void Player::updateHand() { hand_ = Hand(deck_.getHand()); }

bool Player::playCard(const std::shared_ptr<Card>& card) {
  if (!card) {
    return false;
  }
  if (elixir_ >= card->getCost()) {
    elixir_ -= card->getCost();
    deck_.playCard(card);
    this->updateHand();
    return true;
  } else {
    std::cout << "Not enough elixir to play " << card->getName() << "!\n";
    return false;
  }
}

int Player::getElixir() const { return elixir_; }

const Hand& Player::getHand() const { return hand_; }

Hand& Player::getHand() { return hand_; }

const Deck& Player::getDeck() const { return deck_; }

Deck& Player::getDeck() { return deck_; }

const std::string& Player::getName() const { return name_; }

const TowerType& Player::getTowerType() const { return towerType_; }

void Player::setColor(const sf::Color& color) { color_ = color; }

const sf::Color& Player::getColor() const { return color_; }

void Player::reset() {
  elixir_ = 0;
  elixirTimer_ = 0.0f;
  deck_.shuffle();
  hand_ = Hand(deck_.initializedHand());
}
