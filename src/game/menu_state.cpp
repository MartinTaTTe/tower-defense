#include "menu_state.hpp"
#include "game_state.hpp"
#include "../utils/texture_manager.hpp"
#include "../utils/app_constants.hpp"
//#include "input_state.hpp"

MenuState::MenuState(int width, int height)
    : State("Menu State", width, height) {
    AddCanvas({0.0f, 0.0f, 0.5f, 0.5f});
    Event event(EventType::PushState);
    event.state = new GameState(width, height, M_BASIC_MAP);
    canvases_.back().second->AddButton({0.3f, 0.3f, 0.8f, 0.9f}, T_DEFAULT_BUTTON, event);
}
