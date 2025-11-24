#pragma once

#include "../../src/players/Deck.hpp"
#include "spells.hpp"
#include "units.hpp"

inline Deck defaultDeck = Deck(std::vector<std::shared_ptr<Card>>{
    std::make_shared<UnitCard>(HogRider),
    std::make_shared<UnitCard>(BigRider),
    std::make_shared<UnitCard>(MiniRider),
    std::make_shared<UnitCard>(FatRider),
    std::make_shared<UnitCard>(DickRider),
    std::make_shared<UnitCard>(RangedRider),
    std::make_shared<SpellCard>(Fireball),
    std::make_shared<SpellCard>(Zap)
});