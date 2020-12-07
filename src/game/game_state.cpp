#include "game_state.hpp"
#include "../utils/app_constants.hpp"
#include "../utils/texture_manager.hpp"

#include <fstream>
#include <iostream>

GameState::GameState(int width, int height, const std::string& mapPath)
    : State("Game State", width, height), since_last_spawn_(SPAWN_SPEED - 1), player_lives_(PLAYER_LIVES) {
    AddCanvas({0, 0, 0.8f, 1}, mapPath); // map
    start_ = dynamic_cast<Map*>(canvases_.back().second)->GetStart();
    canvases_.back().second->AddText({0.8f, 0}, "10 lives", 30); // life counter
    AddCanvas({0.8f, 0, 1, 1}); // siderbar
    canvases_.back().second->AddButton({0, 0.8f, 1, 1}, T_RETURN_TO_MENU_BUTTON, Event(EventType::PopState)); // return to menu
    canvases_[0].second->AddText({0, 0}, "0 FPS", 30); // FPS counter
    canvases_.back().second->AddButton({0, 0.6f, 1, 0.8f}, T_DEFAULT_BUTTON, Event(EventType::Pause)); // pause button
    canvases_.back().second->AddButton({0, 0.4f, 1, 0.6f}, T_DEFAULT_BUTTON, Event(EventType::SendWave)); // pause button
    Event event(EventType::SelectTower);
    event.tower_type = 'B';
    canvases_.back().second->AddButton({0, 0, 1, 0.2f}, T_BASIC_TOWER, event); // tower button
    ReadWaves();
}

void GameState::Update(double d_time) {
    canvases_[0].second->UpdateString(1, std::to_string((int)(1.0 / d_time)) + " FPS");
    canvases_[0].second->UpdateString(0, std::to_string(player_lives_) + " lives");
    if (!paused_) {
        since_last_spawn_ += d_time;
        if (!wave_.empty() && since_last_spawn_ > SPAWN_SPEED) {
            SendEnemy();
            since_last_spawn_ = 0;
        }
        Event event = dynamic_cast<Map*>(canvases_[0].second)->UpdateEnemies(width_, height_, d_time);
        switch(event.type) {
            case EventType::Dead:
                player_lives_ = player_lives_ - event.increments.x;
                break;
            default:
                break;
        }
        dynamic_cast<Map*>(canvases_[0].second)->UpdateTowers(width_, height_, d_time, Event());
    }
}

Event GameState::CustomOnClick(Event event) {
    Event return_event;
    switch (event.type) {
        case EventType::Pause:
            paused_ = !paused_;
            break;
        case EventType::SendWave:
            AddWave();
            break;
        case EventType::PopState:
            return event;
            break;
        case EventType::SelectTower:
            selected_tower_ = event.tower_type;
            break;
        case EventType::MouseClickReleased:
            if (event.coords.x < width_ * MAP_WIDTH) {
                event.tower_type = selected_tower_;
                dynamic_cast<Map*>(canvases_[0].second)->UpdateTowers(width_, height_, 0, event);
            }
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

void GameState::AddWave() {
    if (!waves_.empty()) {
        for (auto enemy : waves_.back()) {
            for (int i = 0; i < enemy.first; i++) 
                wave_.push_back(enemy.second);
        }
        waves_.pop_back();
    }
}

void GameState::SendEnemy() {
    Map* map = dynamic_cast<Map*>(canvases_[0].second);
    Vector2i grid_size = map->GetGridSize();
    if (!wave_.empty()) {
        map->AddEnemy({
            1.0f / grid_size.x * start_.x,
            1.0f / grid_size.y * start_.y,
            1.0f / grid_size.x * (start_.x + 1),
            1.0f / grid_size.y * (start_.y + 1)
        }, wave_.back());
        wave_.pop_back();
    }
}
