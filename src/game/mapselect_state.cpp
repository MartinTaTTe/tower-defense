#include "mapselect_state.hpp"
#include "game_state.hpp"
#include "../utils/texture_manager.hpp"
#include "../utils/app_constants.hpp"

MapSelectState::MapSelectState(int width, int height)
    : State("Menu State", width, height) {
    AddCanvas({0, 0, 1, 1});
    Event event(EventType::PushGameState);
    event.x = 1;
    canvases_.back().second->AddButton({0.0f, 0.3f, 0.2f, 0.7f}, T_EASY_MAP, event);
    event.x = 2;
    canvases_.back().second->AddButton({0.25f, 0.3f, 0.45f, 0.7f}, T_MEDIUM_MAP, event);
    event.x = 3;
    canvases_.back().second->AddButton({0.5f, 0.3f, 0.7f, 0.7f}, T_HARD_MAP, event);
    event.x = 4;
    canvases_.back().second->AddButton({0.75f, 0.3f, 0.95f, 0.7f}, T_BASIC_MAP, event);
    canvases_.back().second->AddButton({0.7f, 0.8f, 1, 1}, T_RETURN_TO_MENU_BUTTON, Event(EventType::PopState));
}