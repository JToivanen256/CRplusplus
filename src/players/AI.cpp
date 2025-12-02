#include "AI.hpp"

#include "../game/Match.hpp"

std::unique_ptr<Move> AI::play(Match& match) {
  switch (difficulty_) {
    // Play cheapest units from the back or spell-nuke king tower...test
    // difficulty basically
    case Vihannes:
      for (const auto& card : this->getHand().getCards()) {
        if (this->getElixir() >= card->getCost()) {
          if (!card->isSpell()) {
            int col = match.getMap().getGrid().getColumns() / 2;
            int row = 30;
            return std::make_unique<Move>(Move{row, col, card});
          } else if (card->isSpell()) {
            int col = match.getMap().getGrid().getColumns() / 2 - 1;
            int row = match.getMap().getGrid().getRows() - 5;
            return std::make_unique<Move>(Move{row, col, card});
          }
        }
      }
      break;

    case Retardi:  // TODO
      break;

    case Cheater:  // TODO
      break;
  }
  return nullptr;  // No move this time
}