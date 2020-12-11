#include "game_state.hpp"
#include "../utils/app_constants.hpp"
#include "../utils/texture_manager.hpp"

#include <fstream>
#include <iostream>

GameState::GameState(int width, int height, const std::string& mapPath, const std::string& wavePath)
    : State("Game State", width, height), since_last_spawn_(SPAWN_SPEED - 1), player_lives_(PLAYER_LIVES), wave_count_(0), player_gold_(START_GOLD), paused_(false), last_wave_(0) {
    AddCanvas({0, 0, MAP_WIDTH, MAP_HEIGHT}, mapPath); // map
    start_ = dynamic_cast<Map*>(canvases_.back().second)->GetStart();
    canvases_.back().second->AddText({0.8f, 0}, "10 lives", 30); // life counter
    canvases_.back().second->AddText({0.4f, 0}, "Wave 0", 30); // wave counter
    canvases_.back().second->AddText({0, 0}, "Gold " + std::to_string(player_gold_), 30); // Gold counter
    AddCanvas({MAP_WIDTH, 0, 1, 1}); // siderbar
    canvases_.back().second->AddButton({0, 0.9f, 1, 1}, T_RETURN_TO_MENU_BUTTON, Event(EventType::PopState)); // return to menu
    canvases_.back().second->AddButton({0, 0.8f, 1, 0.9f}, T_PLAY_PAUSE_BUTTON, Event(EventType::Pause)); // pause button
    canvases_.back().second->AddButton({0, 0.7f, 1, 0.8f}, T_NEXT_WAVE_BUTTON, Event(EventType::SendWave)); // next wave button
    Event event(EventType::SelectTower);
    event.tower_type = 'B';
    canvases_.back().second->AddButton({0, 0, 0.5f, 0.116f}, T_BASIC_TOWER, event); // tower button
    canvases_.back().second->AddText({0.5f, 0}, MakeDesc(BASIC_TOWER_PRICE, BASIC_TOWER_DAMAGE, BASIC_TOWER_RANGE, true, false), 10);
    event.tower_type = 'F';
    canvases_.back().second->AddButton({0, 0.116f, 0.5f, 0.232f}, T_FLYING_TOWER, event);
    canvases_.back().second->AddText({0.5f, 0.116f}, MakeDesc(FLYING_TOWER_PRICE, FLYING_TOWER_DAMAGE, FLYING_TOWER_RANGE, false, true), 10);
    event.tower_type = 'W';
    canvases_.back().second->AddButton({0, 0.232f, 0.5f, 0.348f}, T_WATER_TOWER, event);
    canvases_.back().second->AddText({0.5f, 0.232f}, MakeDesc(WATER_TOWER_PRICE, WATER_TOWER_DAMAGE, WATER_TOWER_RANGE, true, false), 10);
    event.tower_type = 'H';
    canvases_.back().second->AddButton({0, 0.348f, 0.5f, 0.464f}, T_HYBRID_TOWER, event);
    canvases_.back().second->AddText({0.5f, 0.348f}, MakeDesc(HYBRID_TOWER_PRICE, HYBRID_TOWER_DAMAGE, HYBRID_TOWER_RANGE, true, true), 10);
    event.tower_type = 'U';
    canvases_.back().second->AddButton({0, 0.464f, 0.5f, 0.58f}, T_UTILITY_TOWER, event);
    canvases_.back().second->AddText({0.5f, 0.464f}, MakeDesc(UTILITY_TOWER_PRICE, 0, 0, false, false), 10);
    event.tower_type = 'M';
    canvases_.back().second->AddButton({0, 0.58f, 0.5f, 0.696f}, T_MULTIPLE_TOWER, event);
    canvases_.back().second->AddText({0.5f, 0.58f}, MakeDesc(MULTIPLE_TOWER_PRICE, MULTIPLE_TOWER_DAMAGE, MULTIPLE_TOWER_RANGE, true, false), 10);
    ReadWaves(wavePath);
}

void GameState::Update(double d_time) {
    canvases_[0].second->UpdateString(0, std::to_string(player_lives_) + (player_lives_ == 1 ? " life" : " lives"));
    canvases_[0].second->UpdateString(2, "Gold " + std::to_string((int)player_gold_));
    if (player_lives_ <= 0) {
        paused_ = true;
        canvases_[0].second->AddText({0.1f, 0.35f}, "GAME OVER", 120, sf::Color::Red);
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
        Event towerEvent = dynamic_cast<Map*>(canvases_[0].second)->UpdateTowers(d_time, Event());
        switch (towerEvent.type)
        {
        case EventType::AddGold:
            player_gold_ += towerEvent.damage;
            break;
        default:
            if (wave_count_ == last_wave_ && wave_.empty()) {
                paused_ = true;
                canvases_[0].second->AddText({0.2f, 0.35f}, "VICTORY!", 120, sf::Color::White);
            }
            break;
        }
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
                case 'F':
                    if (player_gold_ >= FLYING_TOWER_PRICE)
                        if (dynamic_cast<Map*>(canvases_[0].second)->UpdateTowers(0, event).condition)
                            player_gold_ -= FLYING_TOWER_PRICE;
                    break;
                case 'W':
                    if (player_gold_ >= WATER_TOWER_PRICE)
                        if (dynamic_cast<Map*>(canvases_[0].second)->UpdateTowers(0, event).condition)
                            player_gold_ -= WATER_TOWER_PRICE;
                    break;
                case 'H':
                    if (player_gold_ >= HYBRID_TOWER_PRICE)
                        if (dynamic_cast<Map*>(canvases_[0].second)->UpdateTowers(0, event).condition)
                            player_gold_ -= HYBRID_TOWER_PRICE;
                    break;
                case 'U':
                    if (player_gold_ >= UTILITY_TOWER_PRICE)
                        if (dynamic_cast<Map*>(canvases_[0].second)->UpdateTowers(0, event).condition)
                            player_gold_ -= UTILITY_TOWER_PRICE;
                    break;
                case 'M':
                    if (player_gold_ >= MULTIPLE_TOWER_PRICE)
                        if (dynamic_cast<Map*>(canvases_[0].second)->UpdateTowers(0, event).condition)
                            player_gold_ -= MULTIPLE_TOWER_PRICE;
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
            last_wave_++;
        }
        file.close();
    }
}

void GameState::AddWave() {
    if (!waves_.empty()) {
        player_gold_ += WAVE_GOLD;
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

std::string GameState::MakeDesc(int price, float damage, int range, bool ground, bool air) {
    std::string desc = "Price: ";
    desc.append(std::to_string(price));
    desc.append("\nDamage: ");
    desc.append(std::to_string((int)damage));
    desc.append("\nRange: ");
    desc.append(std::to_string(range));
    desc.append("\nTargets: ");
    desc.append(ground ? "Grd" : "-");
    desc.append("/");
    desc.append(air ? "Air" : "-");
    return desc;
}
