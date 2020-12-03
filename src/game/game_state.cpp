#include "game_state.hpp"
#include "../utils/app_constants.hpp"
#include <iostream>

GameState::GameState(const std::string& mapPath)
    : map_(new Map({0, 0, WINDOW_WIDTH, WINDOW_HEIGHT}, mapPath)), State("Game State") { }

Event GameState::EventHandler(const sf::Event& sf_event) {
    Event event(EventType::None);
    switch (sf_event.type) {
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
            std::cout << "Resized" << std::endl;
            event.type = EventType::Resize;
            event.body.upper_left_x = 0;
            event.body.upper_left_y = 0;
            event.body.lower_right_x = MAP_WIDTH * sf_event.size.width;
            event.body.lower_right_y = sf_event.size.height;
            event = map_->EventHandler(event);
            break;
    }
    return event;
}

void GameState::Draw(sf::RenderWindow& window) {
    map_->Draw(window);
}
