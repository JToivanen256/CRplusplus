#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

#include "../assets/Cards and Decks/decks.hpp"  // For default Deck
#include "players/AI.hpp"
#include "players/Deck.hpp"
#include "players/Player.hpp"
#include "ui/MatchState.hpp"
#include "ui/MenuState.hpp"
#include "ui/EndState.hpp"

int main() {
  sf::RenderWindow window(sf::VideoMode(390, 780), "SFML App");

  Player player1 = Player("Test", defaultDeck);
  Player player2 = Player("Test2", defaultDeck);

  std::unique_ptr<GameState> currentState = std::make_unique<MenuState>(window);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      currentState->handleInput(window, event);
      if (event.type == sf::Event::Closed) window.close();
    }

    currentState->update(0.016f);

    window.clear();
    currentState->render(window);
    window.display();

    // If in MenuState and ongoingMatch_ is true, switch to MatchState
    if (MenuState* menu = dynamic_cast<MenuState*>(currentState.get())) {
      if (menu->ongoingMatch_) {
        currentState = std::make_unique<MatchState>(player1, player2);
      }
    }

      // If in MatchState and matchOver_ is true, switch to EndState
    if (MatchState* match = dynamic_cast<MatchState*>(currentState.get())) {
      if (match->matchOver_) {
        currentState = std::make_unique<EndState>(window);
      }
    }

    // If in EndState and returnToMenu_ is true, switch to MenuState
    if (EndState* end = dynamic_cast<EndState*>(currentState.get())) {
      if (end->returnToMenu_) {
        currentState = std::make_unique<MenuState>(window);
      }
    }
  }

  return 0;
}