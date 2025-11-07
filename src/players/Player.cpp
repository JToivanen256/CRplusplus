#include "Player.hpp"

Player::Player(const std::string& name, Deck deck)
  : name_(name), deck_(deck), elixir_(0) {
}