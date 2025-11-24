#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

#include "../players/Player.hpp"

/*struct GridPos {
  int x;
  int y;
};*/

/*struct Pos {
  int x;
  int y;
};*/

class Entity {
 protected:
  //GridPos gridPosition_;
  sf::Vector2f position_;
  int maxHealth_;  // For health bar calculations
  int health_;
  int damage_;
  float currentCooldown_ = 0.0f;
  float attackCooldown_;
  float attackRange_;
  bool isAlive_ = true;
  sf::Sprite sprite_;
  sf::Texture texture_;
  Player* owner_;
  Entity* target_ = nullptr;

 public:
  Entity(float x, float y, int health, int damage,
         float attackCooldown, float attackRange, Player* owner)
      : position_{x, y},
        //gridPosition_{gridX, gridY},
        health_(health),
        maxHealth_(health),
        damage_(damage),
        attackCooldown_(attackCooldown),
        attackRange_(attackRange),
        owner_(owner) {}

  virtual ~Entity() = default;

  int getHealth() const { return health_; }

  //GridPos getGridPosition() { return gridPosition_; }
  sf::Vector2f getPosition() { return position_; }

  sf::Sprite& getSprite() { return sprite_; }

  const sf::Sprite& getSprite() const { return sprite_; }

  // Can attack only if not on cooldown, Combat class should handle combat and
  // ask if units aren't on cooldown
  bool canAttack() const { return currentCooldown_ <= 0.0f; };
  Player* getOwner() const { return owner_; }
  virtual void attack(Entity& target) {
    target.takeDamage(damage_);
    currentCooldown_ = attackCooldown_;
  }

  virtual void update(float deltaTime) = 0;

  void takeDamage(int amount) {
    health_ -= amount;
    if (health_ <= 0) {
      health_ = 0;
      isAlive_ = false;
    }
  }

  bool isDead() const { return !isAlive_; }

  void draw(sf::RenderWindow& window) {
    window.draw(sprite_);

    // Draw health bar above the entity
    const sf::FloatRect bounds = sprite_.getGlobalBounds();
    const float barWidth = bounds.width;
    const float barHeight = 3.f;
    const float padding = 3.f;
    const float x = bounds.left;
    const float y = bounds.top - barHeight - padding;

    float healthPercent =
        static_cast<float>(health_) / static_cast<float>(maxHealth_);
    sf::RectangleShape backgroundBar(sf::Vector2f(barWidth, barHeight));
    backgroundBar.setFillColor(sf::Color(50, 50, 50, 200));
    backgroundBar.setPosition(x, y);
    backgroundBar.setOutlineColor(sf::Color::Black);
    backgroundBar.setOutlineThickness(1.f);

    sf::RectangleShape healthBar(
        sf::Vector2f(barWidth * healthPercent, barHeight));
    healthBar.setFillColor(owner_->getColor());
    healthBar.setPosition(x, y);

    window.draw(backgroundBar);
    window.draw(healthBar);
  }

  void setTexture(const sf::Texture& text) {
    texture_ = text;
    sprite_.setTexture(texture_);
    auto size = texture_.getSize();
    sprite_.setOrigin(size.x * 0.5f, size.y * 0.5f);
    sprite_.setPosition((float)position_.x, (float)position_.y);
  }

  auto getSpriteBounds() { return sprite_.getGlobalBounds(); }
};

#endif