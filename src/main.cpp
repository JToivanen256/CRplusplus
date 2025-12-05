#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

#include "../assets/Cards and Decks/decks.hpp"  // For default Deck
#include "players/AI.hpp"
#include "players/Deck.hpp"
#include "players/Player.hpp"
#include "ui/EndState.hpp"
#include "ui/MatchState.hpp"
#include "ui/MenuState.hpp"
#include "ui/PauseState.hpp"

int main() {
  sf::RenderWindow window(sf::VideoMode(390, 780), "CR++");
  sf::Clock clock;

  Player player1 = Player("Test", defaultDeck);
  // Player player2 = Player("Test2", defaultDeck);
  AI player2 = AI("AI", defaultDeck, Retardi);

  std::unique_ptr<GameState> currentState = std::make_unique<MenuState>(window);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      currentState->handleInput(window, event);
      if (event.type == sf::Event::Closed) window.close();
    }

    float deltaTime = clock.restart().asSeconds();

    currentState->update(1 * deltaTime);

    window.clear();
    currentState->render(window);
    window.display();

    // If in MenuState and ongoingMatch_ is true, switch to MatchState
    if (MenuState* menu = dynamic_cast<MenuState*>(currentState.get())) {
      if (menu->ongoingMatch_) {
        player1.reset();
        player2.reset();
        player2.setDifficulty(menu->getAIDifficulty());  // Update AI difficulty
        currentState = std::make_unique<MatchState>(player1, player2);
      }
    }

    // If in MatchState and matchOver_ is true, switch to EndState
    if (MatchState* match = dynamic_cast<MatchState*>(currentState.get())) {
      if (match->matchOver_) {
        std::string winner = match->getWinnerName();
        currentState = std::make_unique<EndState>(window, winner);
      }
    }

    // If in EndState and returnToMenu_ is true, switch to MenuState
    if (EndState* end = dynamic_cast<EndState*>(currentState.get())) {
      if (end->returnToMenu_) {
        currentState = std::make_unique<MenuState>(window);
      }
    }

    // If in MatchState and pause requested, switch to PauseState
    if (MatchState* match = dynamic_cast<MatchState*>(currentState.get())) {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
        // Save current MatchState into PauseState to resume later
        auto prev = std::move(currentState);
        currentState = std::make_unique<PauseState>(window, std::move(prev));
      }
    }

    // If in PauseState and resumeGame_ is true, switch back to MatchState
    if (PauseState* pause = dynamic_cast<PauseState*>(currentState.get())) {
      if (pause->resumeGame_) {
        currentState = pause->getPreviousState();
      } else if (pause->returnToMenu_) {
        currentState = std::make_unique<MenuState>(window);
      }
    }
  }

  return 0;
}