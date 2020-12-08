#include "game_state.hpp"
#include "../utils/app_constants.hpp"
#include "../utils/texture_manager.hpp"

#include <fstream>
#include <iostream>

GameState::GameState(int width, int height, const std::string& mapPath)
    : State("Game State", width, height), since_last_spawn_(SPAWN_SPEED - 1), player_lives_(PLAYER_LIVES), wave_count_(0), player_gold_(START_GOLD), paused_(false) {
    AddCanvas({0, 0, MAP_WIDTH, MAP_HEIGHT}, mapPath); // map
    start_ = dynamic_cast<Map*>(canvases_.back().second)->GetStart();
    canvases_.back().second->AddText({0.8f, 0}, "10 lives", 30); // life counter
    canvases_.back().second->AddText({0.4f, 0}, "Wave 0", 30); // wave counter
    canvases_.back().second->AddText({0.2f, 0}, "Gold " + std::to_string(player_gold_), 30); // Gold counter
    AddCanvas({MAP_WIDTH, 0, 1, 1}); // siderbar
    canvases_.back().second->AddButton({0, 0.8f, 1, 1}, T_RETURN_TO_MENU_BUTTON, Event(EventType::PopState)); // return to menu
    canvases_.back().second->AddButton({0, 0.6f, 1, 0.8f}, T_DEFAULT_BUTTON, Event(EventType::Pause)); // pause button
    canvases_.back().second->AddButton({0, 0.4f, 1, 0.6f}, T_DEFAULT_BUTTON, Event(EventType::SendWave)); // pause button
    Event event(EventType::SelectTower);
    event.tower_type = 'B';
    canvases_.back().second->AddButton({0, 0, 1, 0.2f}, T_BASIC_TOWER, event); // tower button
    ReadWaves();
}

void GameState::Update(double d_time) {
    canvases_[0].second->UpdateString(0, std::to_string(player_lives_) + (player_lives_ == 1 ? " life" : " lives"));
    canvases_[0].second->UpdateString(2, "Gold " + std::to_string(player_gold_));
    if (player_lives_ <= 0) {
        paused_ = true;
        canvases_[0].second->AddText({0, 0.4f}, "GAME OVER", 100, sf::Color::Red);
    }
    if (!paused_) {
        since_last_spawn_ += d_time;
        if (!wave_.empty() && since_last_spawn_ > SPAWN_SPEED) {
            SendEnemy();
            since_last_spawn_ = 0;
        }
        Event event = dynamic_cast<Map*>(canvases_[0].second)->UpdateEnemies(d_time);
        switch(event.type) {
            case EventType::Dead:
                player_lives_ = player_lives_ - event.increments.x;
                player_gold_ = player_gold_ + event.increments.y;
                break;
            default:
                break;
        }
        dynamic_cast<Map*>(canvases_[0].second)->UpdateTowers(d_time, Event());
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
            if (event.x_f < MAP_WIDTH && event.y_f < MAP_HEIGHT) {
                event.tower_type = selected_tower_;
                switch (selected_tower_)
                {
                case 'B':
                    if (player_gold_ >= BASIC_TOWER_PRICE)
                        if (dynamic_cast<Map*>(canvases_[0].second)->UpdateTowers(0, event).condition)
                            player_gold_ -= BASIC_TOWER_PRICE;
                    break;
                default:
                    break;
                }
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
        wave_count_++;
        canvases_[0].second->UpdateString(1, "Wave " + std::to_string(wave_count_));
    }
}

void GameState::SendEnemy() {
    Map* map = dynamic_cast<Map*>(canvases_[0].second);
    Vector2i grid_size = map->GetGridSize();
    if (!wave_.empty()) {
        map->AddEnemy({
            1.0f / grid_size.x * start_.x,
            1.0f / grid_size.y * start_.y
        }, wave_.back());
        wave_.pop_back();
    }
}
