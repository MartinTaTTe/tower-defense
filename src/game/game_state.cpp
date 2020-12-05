#include "game_state.hpp"
#include "../utils/app_constants.hpp"
#include "../utils/texture_manager.hpp"
#include <iostream>

GameState::GameState(int width, int height, const std::string& mapPath)
    : State("Game State", width, height) {
    AddCanvas({0, 0, 0.8f, 1}, mapPath);
    AddCanvas({0.8f, 0, 1, 1}); // siderbar
    canvases_.back().second->AddButton({0, 0.8f, 1, 1}, T_RETURN_TO_MENU, Event(EventType::PopState)); // return to menu
    canvases_[0].second->AddText({0, 0}, "0 FPS", 30); // FPS counter
}

void GameState::Update(double d_time) {
    canvases_[0].second->UpdateString(0, std::to_string((int)(1.0 / d_time)) + " FPS");
    dynamic_cast<Map*>(canvases_[0].second)->CustomUpdate(width_, height_, d_time);
}
