#include "game_state.hpp"
#include "../utils/app_constants.hpp"
#include "../utils/texture_manager.hpp"

GameState::GameState(int width, int height, const std::string& mapPath)
    : State("Game State", width, height) {
    AddMap({0, 0, 0.8f, 1}, mapPath);
    AddCanvas({0.8f, 0, 1, 1});
    canvases_.back().second->AddButton({0, 0.8f, 1, 1}, T_DEFAULT_BUTTON, Event(EventType::PopState));
}
