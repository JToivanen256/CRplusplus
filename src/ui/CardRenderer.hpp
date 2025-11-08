#ifndef CARDRENDERER_HPP
#define CARDRENDERER_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <string>

#include "../players/Card.hpp"

class CardRenderer {
 public:
  static CardRenderer& getInstance();

  void renderCard(const Card& card, sf::RenderWindow& window,
                  const sf::Vector2f& position,
                  const sf::Vector2f& scale) const;

 private:
  CardRenderer();
  bool loadTexture(const std::string& spritePath);

  std::map<std::string, sf::Texture> textures_;
  static std::unique_ptr<CardRenderer> instance_;
};

#endif