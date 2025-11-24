#include "Unit.hpp"

#include <cmath>

// Some helper functions here

static inline sf::Vector2f dirToVec(Direction dir) {
  switch (dir) {
    case Direction::Up:
      return {0.f, -1.f};
    case Direction::Down:
      return {0.f, 1.f};
    case Direction::Left:
      return {-1.f, 0.f};
    case Direction::Right:
      return {1.f, 0.f};
    case Direction::UpLeft:
      return {-1.f, -1.f};
    case Direction::UpRight:
      return {1.f, -1.f};
    case Direction::DownLeft:
      return {-1.f, 1.f};
    case Direction::DownRight:
      return {1.f, 1.f};
    default:
      return {0.f, 0.f};
  }
}

static inline void normalize(sf::Vector2f& v) {
  float len2 = v.x * v.x + v.y * v.y;
  if (len2 > 0.f) {
    float inv = 1.f / std::sqrt(len2);
    v.x *= inv;
    v.y *= inv;
  }
}

static inline float dist2(const sf::Vector2f& a, const sf::Vector2f& b) {
  float dx = a.x - b.x;
  float dy = a.y - b.y;
  return dx * dx + dy * dy;
}

// this is where the fun starts

void Unit::move(Direction dir, float dt) {
  sf::Vector2f v = dirToVec(dir);
  normalize(v);
  v *= movementSpeed_ * dt;
  const sf::Vector2f next = position_ + v;
  if (!CanMoveTo_ || CanMoveTo_(next)) {
    position_ = next;
  }
}

void Unit::moveToward(const sf::Vector2f& dest, float dt) {
  sf::Vector2f v = dest - position_;
  normalize(v);
  v *= movementSpeed_ * dt;
  const sf::Vector2f next = position_ + v;
  if (!CanMoveTo_ || CanMoveTo_(next)) {
    position_ = next;
  }
}
// finds the nearest enemy, building or unit to attack
/*Entity* Unit::scanNearestEnemy(const std::vector<Entity*>& all) const {
  const float r2 = visionRange_ * visionRange_;
  const sf::Vector2f me = position_;

  Entity* closest = nullptr;
  float closest_dist = std::numeric_limits<float>::max();

  for (Entity* e : all) {
    if (!e || e == this || e->isDead() || e->getOwner() == this->owner_)
      continue;  // Can't have the unit try to attack itself or friendly units
                 // or buildings
    sf::Vector2f ep{static_cast<float>(e->getPosition().x),
                    static_cast<float>(e->getPosition().y)};
    float dist = dist2(me, ep);
    if (dist <= r2) {
      if (dist < closest_dist) {
        closest_dist = dist;
        closest = e;
      }
    }
  }
  return closest;
}*/
static inline sf::Vector2f clampPointToRect(const sf::FloatRect& r, const sf::Vector2f& p) {
  sf::Vector2f out;
  out.x = std::max(r.left, std::min(r.left + r.width, p.x));
  out.y = std::max(r.top,  std::min(r.top + r.height, p.y));
  return out;
}

std::pair<Entity*, sf::Vector2f> Unit::scanNearestEnemy(const std::vector<Entity*>& all) const {
  const float vision = visionRange_;
  const float r2 = vision * vision;
  const sf::Vector2f me = position_;

  Entity* closest = nullptr;
  float bestEdgeDist2 = std::numeric_limits<float>::max();
  sf::Vector2f bestPoint{0.f, 0.f};

  for (Entity* e : all) {
    if (!e || e == this || e->isDead() || e->getOwner() == this->owner_)
      continue;

    sf::FloatRect b = e->getSpriteBounds();

    sf::Vector2f cp = clampPointToRect(b, me);

    float d2 = dist2(me, cp);
    if (d2 <= r2) {
      if (d2 < bestEdgeDist2) {
        bestEdgeDist2 = d2;
        closest = e;
        bestPoint = cp;
      }
    }
  }

  return { closest, bestPoint };
}

// this draws a circle showing the vision range of an unit and can be used for
// debuggin purposes
void Unit::drawVision(sf::RenderWindow& window, bool visible) const {
  if (visible) {
    return;
  }
  sf::CircleShape c(visionRange_);
  c.setOrigin(visionRange_, visionRange_);
  c.setPosition(position_);
  c.setFillColor(sf::Color(0, 0, 255, 32));
  c.setOutlineColor(sf::Color(0, 0, 255, 128));
  c.setOutlineThickness(1.f);
  window.draw(c);
}
// Syncs the sprite back to the center position of the unit. Can be useful?
void Unit::syncVisual() {
  //position_.x = static_cast<int>(std::round(position_.x));
  //position_.y = static_cast<int>(std::round(position_.y));
  sprite_.setPosition(position_);
}

/*std::string Unit::getName() const {
    return "...";
}*/

void Unit::update(float deltaTime) {
  //std::cout << "Going towards: " << targetPosition_.x << ", " << targetPosition_.y << std::endl;

  if (path_.size() >= 2 && currentPathIndex_ < path_.size()) {
    setTargetPosition(path_[currentPathIndex_]);
    if (dist2(position_, targetPosition_) < 4.f) {
      currentPathIndex_++;
    }
  }

  moveToward(targetPosition_, deltaTime);
  syncVisual();
}

void Unit::setStateAttacking() { currentState_ = State::Attacking; }
void Unit::setStateMoving() { currentState_ = State::Moving; }
State Unit::getCurrentState() const { return currentState_; }

void Unit::setPath(const std::vector<sf::Vector2f>& newPath) {
  path_ = newPath;
  currentPathIndex_ = 1; 
}

void Unit::setTargetPosition(const sf::Vector2f& pos) {
  targetPosition_ = pos;
}

void Unit::setTarget(Entity* target) {
  target_ = target;
}

Entity* Unit::getTarget() const {
  return target_;
}

sf::Vector2f Unit::getLastTargetPoint() const { return targetPosition_; }

void Unit::setLastTargetPoint(const sf::Vector2f& point) { lastTargetPoint_ = point; }
