#include "menu_state.hpp"
#include "game_state.hpp"
#include "../utils/texture_manager.hpp"
#include "../utils/app_constants.hpp"
#include "input_state.hpp"

MenuState::MenuState(int width, int height)
    : State("Menu State", width, height) {
    AddCanvas({0, 0, 1, 1});
    Event event(EventType::PushGameState);
    event.x = 0;
    canvases_.back().second->AddButton({0.35f, 0.5f, 0.65f, 0.9f}, T_CUSTOM_MODE_BUTTON, event); // start custom game
    event.type = EventType::PushMapSelectState;
    canvases_.back().second->AddButton({0.68f, 0.5f, 0.98f, 0.9f}, T_PLAY_BUTTON, event); // start game
    canvases_.back().second->AddButton({0.02f, 0.5f, 0.32f, 0.9f}, T_MAP_EDITOR_BUTTON, Event(EventType::PushInputState)); // go to map editor
    canvases_.back().second->AddText({0.05f, 0}, "Tower Defense", 130, sf::Color::Green); // title
    canvases_.back().second->AddDrawable({0, 0, 1, 1}, T_DEFAULT_TOWER); // background
}
