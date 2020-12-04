#include "menu_state.hpp"
#include "game_state.hpp"
#include "../utils/texture_manager.hpp"
#include "../utils/app_constants.hpp"
#include "input_state.hpp"

MenuState::MenuState(int width, int height)
    : State("Menu State", width, height) {
    AddCanvas({0, 0, 1, 1});
    canvases_.back().second->AddButton({0.5f, 0.5f, 0.8f, 0.9f}, T_DEFAULT_BUTTON, Event(EventType::PushGameState)); // start game
    canvases_.back().second->AddButton({0.1f, 0.5f, 0.4f, 0.9f}, T_DEFAULT_BUTTON, Event(EventType::PushInputState)); // go to map editor
    canvases_.back().second->AddText({0.2f, 0}, "Tower Defense", 100); // title
    canvases_.back().second->AddDrawable({0, 0, 1, 1}, T_DEFAULT_TOWER); // background
}
