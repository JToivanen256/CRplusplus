#include "Unit.hpp"

//Some helper functions here

static inline sf::Vector2f dirToVec(Direction dir){
    switch(dir) {
        case Direction::Up:         return {0.f, -1.f};
        case Direction::Down:       return {0.f, 1.f};
        case Direction::Left:       return {-1.f, 0.f};
        case Direction::Right:      return {1.f, 0.f};
        case Direction::UpLeft:     return {-1.f, -1.f};
        case Direction::UpRight:    return {1.f, -1.f};
        case Direction::DownLeft:   return {-1.f, 1.f};
        case Direction::DownRight:  return {1.f, 1.f};
    }
}


static inline void normalize(sf::Vector2f& v){
    float len2 = v.x * v.x + v.y * v.y;
    if(len2 > 0.f){
        float inv = 1.f / std::sqrt(len2);
        v.x *= inv;
        v.y *= inv;
    }
}

static inline float dist2(const sf::Vector2f& a, const sf::Vector2f& b){
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return dx * dx + dy * dy;
}

void Unit::move(Direction dir, float dt){
    sf::Vector2f v = dirToVec(dir);
    normalize(v);
    v *= movementSpeed_ * dt;
    const sf::Vector2f next = posF_ + v;
    if(!CanMoveTo_ || CanMoveTo_(next)){
        posF_ = next;
    }
}

void Unit::moveToward(const sf::Vector2f& dest, float dt){
    sf::Vector2f v = dest - posF_;
    normalize(v);
    v *= movementSpeed_ * dt;
    const sf::Vector2f next = posF_ + v;
    if(!CanMoveTo_ || CanMoveTo_(next)){
        posF_ = next;
    }
}