#include "CardRenderer.hpp"

#include <iostream>

CardRenderer::CardRenderer() {}

CardRenderer::~CardRenderer() { textures_.clear(); }

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
                              const sf::Vector2f& scale, const sf::Font& font) {
  // Draw fallback by default
  auto drawFallback = [&]() {
    sf::RectangleShape fallback(sf::Vector2f(scale.x * 64.f, scale.y * 64.f));
    fallback.setPosition(position);
    fallback.setFillColor(sf::Color(60, 60, 60));
    fallback.setOutlineColor(sf::Color::White);
    fallback.setOutlineThickness(1.f);
    window.draw(fallback);

    // Also draw card name for clarity using provided font
    sf::Text name(card.getName(), font, 12);
    name.setPosition(position.x + 4.f, position.y + 4.f);
    name.setFillColor(sf::Color::White);
    window.draw(name);
  };

  auto drawCostBadge = [&](int cost) {
    float cardW = scale.x * 64.f;
    float cardH = scale.y * 64.f;
    float badgeRadius = std::max(10.f, cardW * 0.18f);

    //Creates the circle around the elixir cost
    sf::CircleShape badge(badgeRadius);
    badge.setFillColor(sf::Color::White);
    badge.setOutlineColor(sf::Color::Black);
    badge.setOutlineThickness(1.f);

    badge.setPosition(position.x, position.y + 64.f);
    window.draw(badge);

    //Creates the cost text itself
    unsigned int charSize = static_cast<unsigned int>(std::max(10.f, badgeRadius * 0.9f));
    sf::Text costText(std::to_string(cost), font, charSize);
    costText.setFillColor(sf::Color::Black);

    //Centers the cost on top of the circle
    sf::FloatRect tb = costText.getLocalBounds();
    float textX = position.x + badgeRadius - (tb.width / 2.0f) - tb.left;
    float textY = position.y + 64.f + badgeRadius - (tb.height / 2.0f) - tb.top;
    costText.setPosition(textX, textY);
    window.draw(costText);
  };

  // Try to load and render the sprite
  const std::string& spritePath = card.getSpritePath();
  if (!this->loadTexture(spritePath)) {
    drawFallback();
    return;
  }

  auto it = textures_.find(spritePath);
  if (it != textures_.end()) {
    sf::Sprite sprite(it->second);
    sprite.setPosition(position);
    sprite.setScale(scale);
    window.draw(sprite);
    drawCostBadge(card.getCost());
  } else {
    drawFallback();
  }
}