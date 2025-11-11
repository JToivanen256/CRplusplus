#include "Unit.hpp"
#include <cmath>

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
        default:                    return {0.f, 0.f};
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

//this is where the fun starts

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
//finds the nearest enemy, building or unit to attack
Entity* Unit::scanNearestEnemy(const std::vector<Entity*>& all)const{
    const float r2 = visionRange_ * visionRange_;
    const sf::Vector2f me = posF_;

    Entity* closest = nullptr;
    float closest_dist = std::numeric_limits<float>::max();

    for(Entity* e: all){
        if(!e || e == this || e->isDead() || e->getOwner() == this->owner_) continue;                //Can't have the unit try to attack itself or friendly units or buildings
        sf::Vector2f ep{ static_cast<float>(e->getPosition().x),
                         static_cast<float>(e->getPosition().y)};
        float dist = dist2(me, ep);
        if (dist <= r2){
            if(dist < closest_dist){
                closest_dist = dist;
                closest = e;
            }
        }

    }
    return closest;
}


//this draws a circle showing the vision range of an unit and can be used for debuggin purposes
void Unit::drawVision(sf::RenderWindow& window, bool visible)const{
    if(visible){
        return;
    }
    sf::CircleShape c(visionRange_);
    c.setOrigin(visionRange_, visionRange_);
    c.setPosition(posF_);
    c.setFillColor(sf::Color(0, 0, 255, 32));
    c.setOutlineColor(sf::Color(0, 0, 255, 128));
    c.setOutlineThickness(1.f);
    window.draw(c);
}
//Syncs the sprite back to the center position of the unit. Can be useful?
void Unit::syncVisual(){
    position_.x = static_cast<int>(std::round(posF_.x));
    position_.y = static_cast<int>(std::round(posF_.y));
    sprite_.setPosition(posF_);
}