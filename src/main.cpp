#include "ui/MenuState.hpp"
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML App");

    MenuState menuState(window);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            menuState.handleInput(window, event);
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        menuState.render(window);
        window.display();
    }
    
    return 0;
}
