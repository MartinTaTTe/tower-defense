#include "game_state.hpp"

GameState::GameState(const Vector2i& size, const std::string& mapPath)
    : map_(new Map({0, 0, MAP_WIDTH * size.x, (float)size.y}, mapPath)), State("Game State") { }

State* GameState::EventHandler(sf::RenderWindow& window, sf::Event& sf_event) {
    while (window.pollEvent(sf_event)) {
        Event event(EventType::None);
        switch (sf_event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseMoved:
                event.type = EventType::MouseMovement;
                event.coords.x = sf_event.mouseMove.x;
                event.coords.y = sf_event.mouseMove.y;
                map_->EventHandler(event);
                break;
            case sf::Event::MouseButtonPressed:
                event.type = EventType::MouseClick;
                event.coords.x = sf_event.mouseButton.x;
                event.coords.y = sf_event.mouseButton.y;
                map_->EventHandler(event);
                break;
            case sf::Event::Resized:
                event.type = EventType::Resize;
                map_->EventHandler(event);
                break;
        }
    }
    return this;
}

void GameState::Draw(sf::RenderWindow& window) {
    map_->Draw(window);
}
