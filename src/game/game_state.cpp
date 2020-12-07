#include "game_state.hpp"
#include "../utils/app_constants.hpp"
#include "../utils/texture_manager.hpp"

#include <fstream>
#include <iostream>

GameState::GameState(int width, int height, const std::string& mapPath)
    : State("Game State", width, height), since_last_spawn_(SPAWN_SPEED - 1) {
    AddCanvas({0, 0, 0.8f, 1}, mapPath); // map
    start_ = dynamic_cast<Map*>(canvases_.back().second)->GetStart();
    AddCanvas({0.8f, 0, 1, 1}); // siderbar
    canvases_.back().second->AddButton({0, 0.8f, 1, 1}, T_RETURN_TO_MENU_BUTTON, Event(EventType::PopState)); // return to menu
    canvases_[0].second->AddText({0, 0}, "0 FPS", 30); // FPS counter
    canvases_.back().second->AddButton({0, 0.6f, 1, 0.8f}, T_DEFAULT_BUTTON, Event(EventType::Pause)); // pause button
    canvases_.back().second->AddButton({0, 0.4f, 1, 0.6f}, T_DEFAULT_BUTTON, Event(EventType::SendWave)); // pause button
    ReadWaves();
}

void GameState::Update(double d_time) {
    canvases_[0].second->UpdateString(0, std::to_string((int)(1.0 / d_time)) + " FPS");
    if (!paused_) {
        since_last_spawn_ += d_time;
        if (!wave_.empty() && since_last_spawn_ > SPAWN_SPEED) {
            SendWave();
            since_last_spawn_ = 0;
        }
        dynamic_cast<Map*>(canvases_[0].second)->CustomUpdate(width_, height_, d_time);
    }
}

Event GameState::CustomOnClick(Event event) {
    Event return_event;
    switch (event.type) {
        case EventType::Pause:
            paused_ = !paused_;
            break;
        case EventType::SendWave:
            
        case EventType::PopState:
            return_event.type = EventType::PopState;
            break;
        default:
            break;
    }
    return return_event;
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
            map->AddEnemy({
                1.0f / grid_size.x * start_.x,
                1.0f / grid_size.y * start_.y,
                1.0f / grid_size.x * (start_.x + 1),
                1.0f / grid_size.y * (start_.y + 1)
            }, enemy.second);
        }
        waves_.pop_back();
    }
}
