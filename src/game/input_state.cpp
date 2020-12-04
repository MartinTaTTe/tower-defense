#include "input_state.hpp"

InputState::InputState(int width, int height)
    : State("Input State", width, height), grid_width_(2), grid_height_(2) {
    AddCanvas({0.2f, 0.2f, 0.8f, 0.8f});
    Event event(EventType::ChangeMapSize);
    event.increments = {1, 0};
    canvases_.back().second->AddButton({0, 0, 0.45f, 0.2f}, T_DEFAULT_BUTTON, event);
    event.increments = {0, 1};
    canvases_.back().second->AddButton({0.55f, 0, 1, 0.2f}, T_DEFAULT_BUTTON, event);
    event.increments = {-1, 0};
    canvases_.back().second->AddButton({0, 0.5f, 0.45f, 0.7f}, T_DEFAULT_BUTTON, event);
    event.increments = {0, -1};
    canvases_.back().second->AddButton({0.55f, 0.5f, 1, 0.7f}, T_DEFAULT_BUTTON, event);
    canvases_.back().second->AddText({0.2f, 0.3f}, "2", 50);
    canvases_.back().second->AddText({0.7f, 0.3f}, "2", 50);
}

Event InputState::EventHandler(const sf::Event& sf_event) {
    Event event;
    switch (sf_event.type) {
        case sf::Event::Resized:
            OnResize(sf_event.size.width, sf_event.size.height);
            break;
        case sf::Event::MouseMoved:
            OnMouseMovement(sf_event.mouseMove.x, sf_event.mouseMove.y);
            break;
        case sf::Event::MouseButtonPressed:
            event = OnClick(sf_event.mouseButton.x, sf_event.mouseButton.y);
            event = CustomMouseClick(event);
            break;
        default:
            break;
    }
    return event;
}

Event InputState::CustomMouseClick(Event event) {
    Event return_event;
    switch (event.type) {
        case EventType::ChangeMapSize:
            grid_width_  = std::max(grid_width_  + event.increments.x, 2);
            grid_height_ = std::max(grid_height_ + event.increments.y, 2);
            canvases_.back().second->UpdateString(0, std::to_string(grid_width_));
            canvases_.back().second->UpdateString(1, std::to_string(grid_height_));
            break;
        default:
            break;
    }
    return return_event;
}
