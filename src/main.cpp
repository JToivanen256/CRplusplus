#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

#include "../assets/Cards and Decks/decks.hpp"  // For default Deck
#include "players/AI.hpp"
#include "players/Deck.hpp"
#include "players/Player.hpp"
#include "ui/MatchState.hpp"
#include "ui/MenuState.hpp"

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
  }

  return 0;
}
