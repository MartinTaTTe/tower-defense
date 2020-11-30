#include "menu_state.hpp"
#include "texture_manager.hpp"

MenuState::MenuState()
    : State("Menu State") { }

State* MenuState::EventHandler(sf::RenderWindow& window, sf::Event& event) {
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                    return new GameState(new Map("map/maps/basic.map"));
        }
    }
    return this;
}

void MenuState::Draw(sf::RenderWindow& window) {
    sf::RectangleShape menu((sf::Vector2f)window.getSize());
    auto texture = GetTexture("./textures/menu.png");
    texture.setSmooth(true);
    menu.setTexture(&texture);
    window.draw(menu);
}
