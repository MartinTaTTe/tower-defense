#include "menu_state.hpp"
#include "game_state.hpp"
#include "../utils/texture_manager.hpp"
#include "../utils/app_constants.hpp"

MenuState::MenuState()
    : State("Menu State") { }

State* MenuState::EventHandler(sf::RenderWindow& window, sf::Event& event) {
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                    Vector2i size;
                    size.x = window.getSize().x;
                    size.y = window.getSize().y;
                    return new GameState(size, M_BASIC_MAP);
                }
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
