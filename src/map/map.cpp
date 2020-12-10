#include "map.hpp"
#include <fstream>
#include "../utils/path_finder.hpp"
#include "../enemies/enemies.hpp"
#include "../towers/towers.hpp"

Map::Map(const Vector4f& body, const std::string& filePath)
    : Canvas(body) {
    auto path_finder = PathFinder(filePath);
    path_finder.findPath();
    path_ = path_finder.getPath();
    path_length_ = path_.size();
    std::ifstream file(filePath);
    std::string line;
    std::getline(file,line);
    grid_width_  = stoi(line.substr(0, line.find('x')));
    grid_height_ = stoi(line.substr(line.find('x') + 1));
    tile_width_  = 1.0f  / grid_width_;
    tile_height_ = 1.0f / grid_height_;
    std::getline(file,line);
    start_.x = stoi(line.substr(0, line.find(',')));
    start_.y = stoi(line.substr(line.find(',') + 1));
    std::getline(file,line);
    end_.x = stoi(line.substr(0, line.find(',')));
    end_.y = stoi(line.substr(line.find(',') + 1));
    int x = 0;
    int y = 0;
    while(std::getline(file,line)) {
        x = 0;
        for (auto i : line) {
            Vector4f position = {
                tile_width_  * x,
                tile_height_ * y,
                tile_width_  * (x + 1),
                tile_height_ * (y + 1)
            };
            drawables_.push_back(
                std::pair<Vector4f, Drawable*>
                (position, new Tile(body_ * position, static_cast<TileType>(i - '0')))
            );
            x++;
        }
        y++;
    }
    file.close();
}

Map::Map(const Vector4f& body, int grid_width, int grid_height)
    : 
    Canvas(body),
    grid_width_(grid_width),
    grid_height_(grid_height),
    tile_width_(1.0f  / grid_width_),
    tile_height_(1.0f / grid_height_) 
    {
    for(int y = 0; y < grid_height_; y++) {
        for (int x = 0; x < grid_width_; x++) {
           Vector4f position = {
                tile_width_  * x,
                tile_height_ * y,
                tile_width_  * (x + 1),
                tile_height_ * (y + 1)
            };
            drawables_.push_back(
                std::pair<Vector4f, Drawable*>
                (position, new Tile(body_ * position, TileType::Grass))
            );
        }
    }
}

Map::~Map() {
    for (auto enemy : enemies_)
        delete enemy.second;
}

Event Map::UpdateTile(Event event, TileType& tileType, bool highlight) {
    Vector2f relative = body_ / event.position;
    int x = relative.x * grid_width_;
    int y = relative.y * grid_height_;
    event.x = -1;
    if (highlight && GetTile(x, y)->type == TileType::Path) {
        event.x = x;
        event.y = y;
         GetTile(x, y)->Highlight(highlight);
    } else if (!highlight) {
        GetTile(x, y)->type = tileType;
        GetTile(x, y)->UpdateTexture();
    }
    return event;
}

Tile* Map::GetTile(int x, int y) const {
    if (x < grid_width_ && y < grid_height_)
        return dynamic_cast<Tile*>(drawables_[x + y * grid_width_].second);
    else return nullptr;
}

Event Map::UpdateEnemies(double d_time) {
    death_occured_ = false;
    Event return_event;
    return_event.increments = {0, 0};
    for (auto enemy = enemies_.begin(); enemy != enemies_.end(); enemy++) {
        if (enemy->second->currentTile != path_length_ - 1) {
            int d_x = 0, d_y = 0;
            Vector2i next = GetNextTile(enemy->second->currentTile);
            bool reached_x = std::abs((float)next.x - enemy->second->GetX()) < 0.01f;
            bool reached_y = std::abs((float)next.y - enemy->second->GetY()) < 0.01f;
            if (reached_x && reached_y)
                enemy->second->currentTile++;
            if (!reached_x && reached_y && (float)next.x > enemy->second->GetX())
                d_x = 1;
            else if (!reached_x && reached_y && (float)next.x < enemy->second->GetX())
                d_x = -1;
            else if (!reached_y && (float)next.y > enemy->second->GetY())
                d_y = 1;
            else if (!reached_y && (float)next.y < enemy->second->GetY())
                d_y = -1;
            Event newEvent = enemy->second->Update(0, d_time * d_x, d_time * d_y, tile_width_ * MAP_WIDTH, tile_height_ * MAP_HEIGHT);
            if (newEvent.type == EventType::Dead) {
                return_event.type = EventType::Dead;
                return_event.increments.y += enemy->second->GetValue();
                death_occured_ = true;
                delete enemy->second;
                enemy = enemies_.erase(enemy);
                if (enemy == enemies_.end()) break;
                if (enemies_.empty()) break;
            } else if (newEvent.type == EventType::SpawnKill) {
                return_event.type = EventType::Dead;
                return_event.increments.y += enemy->second->GetValue();
                death_occured_ = true;
                int tile = enemy->second->currentTile;
                delete enemy->second;
                enemy = enemies_.erase(enemy);
                Vector2f pos = {
                    1.0f / grid_width_ * newEvent.x_f,
                    1.0f / grid_height_ * newEvent.y_f
                };
                Vector4f position = {
                    pos.x,
                    pos.y,
                    pos.x + tile_width_,
                    pos.y + tile_height_
                };
                enemies_.push_back(
                    std::pair<Vector4f, Enemy*>
                    (position, 
                    new NormalEnemy(body_ * position, newEvent.x_f, newEvent.y_f))
                );
                enemies_.back().second->currentTile = tile;
                if (enemy == enemies_.end()) break;
                if (enemies_.empty()) break;
            }
        } else {
            return_event.type = EventType::Dead;
            return_event.increments.x++;
            death_occured_ = true;
            delete enemy->second;
            enemy = enemies_.erase(enemy);
            if (enemy == enemies_.end()) break;
            if (enemies_.empty()) break;
        }
    }
    return return_event;
}

Event Map::UpdateTowers(double d_time, Event event) {
    if (event.type == EventType::MouseClickReleased) {
        Vector2f relative = body_ / event.position;
        int x = relative.x * grid_width_;
        int y = relative.y * grid_height_;
        Tile* tile = GetTile(x, y);
        if (!tile->occupied) {
            Vector4f position = {
                (float)x     / grid_width_,
                (float)y     / grid_height_,
                (float)(x+1) / grid_width_,
                (float)(y+1) / grid_height_
            };
            Tower* tower;
            switch (event.tower_type)
            {
            case 'B':
                if (tile->type == TileType::Grass) {
                    tower = new BasicTower(body_ * position, x, y);
                    buttons_.push_back(
                        std::pair<Vector4f, Tower*>
                        (position, tower)
                    );
                    tile->occupied = true;
                    event.condition = true;
                } else {
                    event.condition = false;
                }
                break;
            case 'F':
                if (tile->type == TileType::Grass) {
                    tower = new FlyingTower(body_ * position, x, y);
                    buttons_.push_back(
                        std::pair<Vector4f, Tower*>
                        (position, tower)
                    );
                    tile->occupied = true;
                    event.condition = true;
                } else {
                    event.condition = false;
                }
                break;
            case 'W':
                if (tile->type == TileType::Water) {
                    tower = new WaterTower(body_ * position, x, y);
                    buttons_.push_back(
                        std::pair<Vector4f, Tower*>
                        (position, tower)
                    );
                    tile->occupied = true;
                    event.condition = true;
                } else {
                    event.condition = false;
                }
                break;
            case 'H':
                if (tile->type == TileType::Grass) {
                    tower = new HybridTower(body_ * position, x, y);
                    buttons_.push_back(
                        std::pair<Vector4f, Tower*>
                        (position, tower)
                    );
                    tile->occupied = true;
                    event.condition = true;
                } else {
                    event.condition = false;
                }
                break;
            case 'U':
                if (tile->type == TileType::Grass) {
                    tower = new UtilityTower(body_ * position, x, y);
                    buttons_.push_back(
                        std::pair<Vector4f, Tower*>
                        (position, tower)
                    );
                    tile->occupied = true;
                    event.condition = true;
                } else {
                    event.condition = false;
                }
                break;
            case 'M':
                if (tile->type == TileType::Grass) {
                    tower = new MultipleTower(body_ * position, x, y);
                    buttons_.push_back(
                        std::pair<Vector4f, Tower*>
                        (position, tower)
                    );
                    tile->occupied = true;
                    event.condition = true;
                } else {
                    event.condition = false;
                }
                break;
            default:
                event.condition = false;
                break;
            }
        } else {
            event.condition = false;
        }
        
    } else {
        float counter = 0;
        for (auto button : buttons_) {
            Tower* tower = dynamic_cast<Tower*>(button.second);
            event.condition = death_occured_;
            if (tower != nullptr) {
                Event newEvent = tower->Update(enemies_, event, d_time);
                if (newEvent.tower_type == 'U' && !enemies_.empty()) {
                        counter += newEvent.damage;
                } 
            }
        }
        if (!enemies_.empty())
            event.type = EventType::AddGold;
        event.damage = counter;
    }
    return event;
}

Vector2i Map::GetStart() {
    return start_;
}
Vector2i Map::GetEnd() {
    return end_;
}

Vector2i Map::GetGridSize() {
    return {grid_width_, grid_height_};
}

void Map::AddEnemy(const Vector2f& pos, char type) {
    Enemy* enemy;
    Vector4f position = {
        pos.x,
        pos.y,
        pos.x + tile_width_,
        pos.y + tile_height_
    };
    switch (type)
    {
    case 'N':
        enemy = new NormalEnemy(body_ * position, start_.x, start_.y);
        break;
    case 'F':
        enemy = new FastEnemy(body_ * position, start_.x, start_.y);
        break;
    case 'A':
        enemy = new FlyingEnemy(body_ * position, start_.x, start_.y);
        break;
    case 'R':
        enemy = new RegenEnemy(body_ * position, start_.x, start_.y);
        break;
    case 'S':
        enemy = new SpawnEnemy(body_ * position, start_.x, start_.y);
        break;
    default:
        break;
    }
    enemies_.push_back(
        std::pair<Vector4f, Enemy*>
        (position, enemy)
    );
}

void Map::CustomDraw(sf::RenderWindow& window) const {
    for (auto enemy = enemies_.rbegin(); enemy != enemies_.rend(); ++enemy) {
        enemy->second->Draw(window);
        enemy->second->DrawHP(window);
    }
    for (auto button : buttons_) {
        Tower* tower = dynamic_cast<Tower*>(button.second);
        if (tower != nullptr) {
            tower->DrawLine(window, tile_width_, tile_height_);
        }
    }
}

Vector2i Map::GetNextTile(int i) {
    auto next = path_[i + 1];
    return {next.first, next.second};
}
