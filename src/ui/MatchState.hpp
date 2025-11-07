#ifndef MATCHSTATE_HPP
#define MATCHSTATE_HPP

#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "../game/Match.hpp"
#include "../players/Player.hpp"

class MatchState : public GameState {
private:
    Match match_;

public:
    MatchState(Player p1, Player p2); 
    virtual void update(float deltaTime) override;
    virtual void handleInput(sf::RenderWindow& window, sf::Event event) override;
    virtual void render(sf::RenderWindow& window) override;
};

#endif

