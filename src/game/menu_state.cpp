#include "menu_state.hpp"
#include "game_state.hpp"
#include "../utils/texture_manager.hpp"
#include "../utils/app_constants.hpp"
#include "input_state.hpp"

MenuState::MenuState()
    : State("Menu State") { }

Event MenuState::EventHandler(const sf::Event& sf_event) {
    Event event(EventType::None);
    switch (sf_event.type) {
        case sf::Event::KeyPressed:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                event.type = EventType(PushState);
                event.state = new GameState(M_BASIC_MAP);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                event.type = EventType(PushState);
                event.state = new InputState();
            }
            break;
    }
    return event;
}

void MenuState::Draw(sf::RenderWindow& window) {
    sf::RectangleShape menu((sf::Vector2f)window.getSize());
    auto texture = GetTexture("./textures/menu.png");
    texture.setSmooth(true);
    menu.setTexture(&texture);
    window.draw(menu);
}
