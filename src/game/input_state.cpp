#include "input_state.hpp"

InputState::InputState(int width, int height)
    : State("Input State", width, height), grid_width_(2), grid_height_(2) {
    AddCanvas({0.2f, 0.2f, 0.8f, 0.8f}); // main interface
    Event event(EventType::ChangeMapSize);
    event.increments = {1, 0};
    canvases_.back().second->AddButton({0, 0, 0.45f, 0.2f}, T_PLUS_BUTTON, event); // increment x
    event.increments = {0, 1};
    canvases_.back().second->AddButton({0.55f, 0, 1, 0.2f}, T_PLUS_BUTTON, event); // increment y
    event.increments = {-1, 0};
    canvases_.back().second->AddButton({0, 0.5f, 0.45f, 0.7f}, T_MINUS_BUTTON, event); // decrement x
    event.increments = {0, -1};
    canvases_.back().second->AddButton({0.55f, 0.5f, 1, 0.7f}, T_MINUS_BUTTON, event); // decrement y
    canvases_.back().second->AddText({0.15f, 0.2f}, "Width", 40);
    canvases_.back().second->AddText({0.65f, 0.2f}, "Height", 40);
    canvases_.back().second->AddText({0.2f, 0.3f}, "2", 50); // x
    canvases_.back().second->AddText({0.7f, 0.3f}, "2", 50); // y
    AddCanvas({0,0,1,1});
    canvases_.back().second->AddText({0.1f, 0.1f}, "Enter map width and height using the buttons.", 30);
    AddCanvas({0.8f, 0, 1, 1}); // sidebar
    canvases_.back().second->AddButton({0, 0.8f, 1, 1}, T_RETURN_TO_MENU_BUTTON, Event(EventType::PopState)); // return to menu
    canvases_.back().second->AddButton({0, 0, 1, 0.2f}, T_MAP_EDITOR_BUTTON, Event(EventType::PushMapEditorState));
}

Event InputState::CustomOnClick(Event event) {
    Event return_event;
    switch (event.type) {
        case EventType::ChangeMapSize:
            grid_width_  = std::max(grid_width_  + event.increments.x, 2);
            grid_height_ = std::max(grid_height_ + event.increments.y, 2);
            canvases_[0].second->UpdateString(2, std::to_string(grid_width_));
            canvases_[0].second->UpdateString(3, std::to_string(grid_height_));
            break;
        case EventType::PopState:
            return_event.type = EventType::PopState;
            break;
        case EventType::PushMapEditorState:
            return_event.type = EventType::PushMapEditorState;
            return_event.increments.x = grid_width_;
            return_event.increments.y = grid_height_;
            break;
        default:
            break;
    }
    return return_event;
}
