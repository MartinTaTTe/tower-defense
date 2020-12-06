#include "game_state.hpp"
#include "../utils/app_constants.hpp"
#include "../utils/texture_manager.hpp"

#include <fstream>
#include <iostream>

GameState::GameState(int width, int height, const std::string& mapPath)
    : State("Game State", width, height) {
    AddCanvas({0, 0, 0.8f, 1}, mapPath); // map
    start_ = dynamic_cast<Map*>(canvases_.back().second)->GetStart();
    AddCanvas({0.8f, 0, 1, 1}); // siderbar
    canvases_.back().second->AddButton({0, 0.8f, 1, 1}, T_RETURN_TO_MENU_BUTTON, Event(EventType::PopState)); // return to menu
    canvases_[0].second->AddText({0, 0}, "0 FPS", 30); // FPS counter

    ReadWaves();
    SendWave();
}

void GameState::Update(double d_time) {
    canvases_[0].second->UpdateString(0, std::to_string((int)(1.0 / d_time)) + " FPS");
    dynamic_cast<Map*>(canvases_[0].second)->CustomUpdate(width_, height_, d_time);
}

void GameState::ReadWaves(const std::string& filePath) {
    std::ifstream file(filePath);
    if (file.is_open()) {
        std::string line;
        std::string amount = "";
        while(std::getline(file,line)) {
            waves_.push_back(std::vector<std::pair<int, char>>());
            for (auto c : line) {
                if (isdigit(c)) {
                    amount += c;
                } else {
                    waves_.back().push_back(std::pair<int, char>(std::stoi(amount), c));
                    amount = "";
                }
            }
        }
        file.close();
    }
}

void GameState::SendWave() {
    if (!waves_.empty()) {
        Map* map = dynamic_cast<Map*>(canvases_[0].second);
        Vector2i grid_size = map->GetGridSize();
        for (auto enemy : waves_.back()) {
            map->AddDrawable(
                {
                    1.0f / grid_size.x * start_.x,
                    1.0f / grid_size.y * start_.y,
                    1.0f / grid_size.x * (start_.x + 1),
                    1.0f / grid_size.y * (start_.y + 1)
                },
                T_DEFAULT_ENEMY
            );
        }
        waves_.pop_back();
    }
}
