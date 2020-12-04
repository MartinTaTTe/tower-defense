#include "game_state.hpp"
#include "../utils/app_constants.hpp"
#include "../utils/texture_manager.hpp"
#include <iostream>

GameState::GameState(int width, int height, const std::string& mapPath)
    : State("Game State", width, height) {
    AddMap({0, 0, 0.8f, 1}, mapPath);
    AddCanvas({0.8f, 0, 1, 1}); // siderbar
    canvases_.back().second->AddButton({0, 0.8f, 1, 1}, T_RETURN_TO_MENU, Event(EventType::PopState)); // return to menu
    canvases_[0].second->AddText({0, 0}, "0 FPS", 30); // FPS counter
}

Event GameState::EventHandler(double d_time, const sf::Event& sf_event) {
    Event event;
    canvases_[0].second->UpdateString(0, std::to_string((int)(1.0 / d_time)) + " FPS");
    switch (sf_event.type) {
        case sf::Event::Resized:
            OnResize(sf_event.size.width, sf_event.size.height);
            break;
        case sf::Event::MouseMoved:
            OnMouseMovement(sf_event.mouseMove.x, sf_event.mouseMove.y);
            break;
        case sf::Event::MouseButtonPressed:
            event = OnClick(sf_event.mouseButton.x, sf_event.mouseButton.y);
            break;
        default:
            break;
    }
    return event;
}
