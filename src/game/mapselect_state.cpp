#include "mapselect_state.hpp"
#include "game_state.hpp"
#include "../utils/texture_manager.hpp"
#include "../utils/app_constants.hpp"

MapSelectState::MapSelectState(int width, int height)
    : State("Menu State", width, height) {
    AddCanvas({0, 0, 1, 1});
    Event event(EventType::PushGameState);
    event.x = 1;
    canvases_.back().second->AddButton({0.35f, 0.5f, 0.65f, 0.9f}, T_CUSTOM_MODE_BUTTON, event);
    canvases_.back().second->AddButton({0.9f, 0.9f, 1, 1}, T_RETURN_TO_MENU_BUTTON, Event(EventType::PopState));
}