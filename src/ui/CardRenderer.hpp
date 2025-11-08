#ifndef CARDRENDERER_HPP
#define CARDRENDERER_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#include "../players/Card.hpp"

class CardRenderer {
 public:
  CardRenderer();
  ~CardRenderer();

  // Render a card. Provide an sf::Font reference to avoid using temporary fonts
  void renderCard(const Card& card, sf::RenderWindow& window,
                  const sf::Vector2f& position, const sf::Vector2f& scale,
                  const sf::Font& font);

 private:
  bool loadTexture(const std::string& spritePath);

  std::map<std::string, sf::Texture> textures_;
};

#endif