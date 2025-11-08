#include "CardRenderer.hpp"

#include <iostream>

std::unique_ptr<CardRenderer> CardRenderer::instance_;

CardRenderer& CardRenderer::getInstance() {
  if (!instance_) {
    instance_ = std::unique_ptr<CardRenderer>(new CardRenderer());
  }
  return *instance_;
}

CardRenderer::CardRenderer() {}

bool CardRenderer::loadTexture(const std::string& spritePath) {
  // Return true if texture is already loaded
  if (textures_.find(spritePath) != textures_.end()) {
    return true;
  }

  // Try to load the texture
  sf::Texture texture;
  if (!texture.loadFromFile("assets/sprites/" + spritePath)) {
    std::cerr << "Failed to load texture: " << spritePath << std::endl;
    return false;
  }

  // Successfully loaded - store it
  textures_.insert({spritePath, texture});
  return true;
}

void CardRenderer::renderCard(const Card& card, sf::RenderWindow& window,
                              const sf::Vector2f& position,
                              const sf::Vector2f& scale) const {
  // Draw fallback by default
  auto drawFallback = [&]() {
    sf::RectangleShape fallback(sf::Vector2f(scale.x * 64.f, scale.y * 64.f));
    fallback.setPosition(position);
    fallback.setFillColor(sf::Color(60, 60, 60));
    fallback.setOutlineColor(sf::Color::White);
    fallback.setOutlineThickness(1.f);
    window.draw(fallback);

    // Also draw card name for clarity
    sf::Text name(card.getName(), sf::Font(),
                  12);  // TODO: Pass font as parameter if needed
    name.setPosition(position.x + 4.f, position.y + 4.f);
    name.setFillColor(sf::Color::White);
    window.draw(name);
  };

  // Try to load and render the sprite
  const std::string& spritePath = card.getSpritePath();
  if (!instance_->loadTexture(spritePath)) {
    drawFallback();
    return;
  }

  auto it = textures_.find(spritePath);
  if (it != textures_.end()) {
    sf::Sprite sprite(it->second);
    sprite.setPosition(position);
    sprite.setScale(scale);
    window.draw(sprite);
  } else {
    drawFallback();
  }
}