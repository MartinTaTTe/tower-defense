#include "map.hpp"
#include <fstream>
#include <iostream>
#include "../enemies/normal_enemy.hpp"
#include "../utils/path_finder.hpp"


Map::Map(const Vector4i& body, const std::string& filePath)
    : Canvas(body) {
    auto path_finder = Path_Finder(filePath);
    path_finder.findPath();
    path_ = path_finder.getPath();
    path_length_ = path_.size();
    std::ifstream file(filePath);
    std::string line;
    std::getline(file,line);
    grid_width_  = stoi(line.substr(0, line.find('x')));
    grid_height_ = stoi(line.substr(line.find('x') + 1, line.find('x') + 2));
    float tile_width  = 1.0f / grid_width_;
    float tile_height = 1.0f / grid_height_;
    std::getline(file,line);
    start_.x = stoi(line.substr(0, line.find(',')));
    start_.y = stoi(line.substr(line.find(',') + 1, line.find(',') + 2));
    std::getline(file,line);
    end_.x = stoi(line.substr(0, line.find(',')));
    end_.y = stoi(line.substr(line.find(',') + 1, line.find(',') + 2));
    //test som printar ut pathen för en map, för att kolla att den funkar
    /*Path_Finder path(filePath);
    std::cout << path.findPath() << std::endl;
    auto stig = path.getPath();
    for (auto it : stig){
        std::cout << "(" << it.first << ":" << it.second << ")" << std::endl;
    }*/
    //test slut
    int x = 0;
    int y = 0;
    while(std::getline(file,line)) {
        x = 0;
        for (auto i : line) {
            Vector4f position = {
                tile_width  * x,
                tile_height * y,
                tile_width  * (x + 1),
                tile_height * (y + 1)
            };
            drawables_.push_back(
                std::pair<Vector4f, Drawable*>
                (position,
                new Tile({
                    (int)(position.upper_left_x * width_)   + GetPosition().x,
                    (int)(position.upper_left_y * height_)  + GetPosition().y,
                    (int)(position.lower_right_x * width_)  + GetPosition().x,
                    (int)(position.lower_right_y * height_) + GetPosition().y
                }, static_cast<TileType>(i - '0'))));
            x++;
        }
        y++;
    }
    file.close();
    Update(body);
}

Map::Map(const Vector4i& body, int grid_width, int grid_height)
    : Canvas(body), grid_width_(grid_width), grid_height_(grid_height) {
    float tile_width =  1.0f / grid_width_;
    float tile_height = 1.0f / grid_height_;
    for(int y = 0; y < grid_height_; y++) {
        for (int x = 0; x < grid_width_; x++) {
           Vector4f position = {
                tile_width * x,
                tile_height * y,
                tile_width * (x + 1),
                tile_height * (y + 1)
            };
            drawables_.push_back(
                std::pair<Vector4f, Drawable*>
                (position,
                new Tile({
                    (int)(position.upper_left_x * width_)   + GetPosition().x,
                    (int)(position.upper_left_y * height_)  + GetPosition().y,
                    (int)(position.lower_right_x * width_)  + GetPosition().x,
                    (int)(position.lower_right_y * height_) + GetPosition().y
                }, TileType::Grass)));
        }
    }
    Update(body);
}

Map::~Map() {
    for (auto enemy : enemies_)
        delete enemy.second;
}

void Map::UpdateTile(int x, int y, TileType& tileType, bool high) {
    if (high) {
        drawables_[x + y * grid_width_].second->Highlight(high);
    } else {
        delete drawables_[x + y * grid_width_].second;
        Vector4f position = drawables_[x + y * grid_width_].first;
        drawables_[x + y * grid_width_].second = new Tile({
                        (int)(position.upper_left_x * width_)   + GetPosition().x,
                        (int)(position.upper_left_y * height_)  + GetPosition().y,
                        (int)(position.lower_right_x * width_)  + GetPosition().x,
                        (int)(position.lower_right_y * height_) + GetPosition().y
                    }, tileType);
    }
}

Tile* Map::GetTile(int x, int y) const {
    if (x < grid_width_ && y < grid_height_)
        return dynamic_cast<Tile*>(drawables_[x + y * grid_width_].second);
    else return nullptr;
}

Event Map::CustomUpdate(int width, int height, double d_time) {
    Event return_event;
    for (auto enemy : enemies_) {
        if (enemy.second->currentTile != path_length_ - 1) {
            std::cout << "Current tile " << enemy.second->currentTile << std::endl;
            int d_x = 0, d_y = 0;
            Vector2i next = GetNext(enemy.second->currentTile);
            bool reached_x = std::abs((float)next.x - enemy.second->GetX()) < 0.05f;
            bool reached_y = std::abs((float)next.y - enemy.second->GetY()) < 0.05f;
            if (reached_x && reached_y)
                enemy.second->currentTile++;
            if (!reached_x && reached_y && (float)next.x > enemy.second->GetX())
                d_x = 1;
            else if (!reached_x && reached_y && (float)next.x < enemy.second->GetX())
                d_x = -1;
            else if (!reached_y && (float)next.y > enemy.second->GetY())
                d_y = 1;
            else if (!reached_y && (float)next.y < enemy.second->GetY())
                d_y = -1;
            return_event = enemy.second->Update(0, d_time * d_x, d_time * d_y);
        } else {
            delete enemy.second;
            enemies_.pop_back();
            return_event.type = EventType::Dead;
        }
    }
    return return_event;
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

void Map::AddEnemy(const Vector4f& position, char type) {
    Enemy* enemy;
    switch (type)
    {
    case 'N':
        enemy = new NormalEnemy(
            {
                (int)(position.upper_left_x * width_)   + GetPosition().x,
                (int)(position.upper_left_y * height_)  + GetPosition().y,
                (int)(position.lower_right_x * width_)  + GetPosition().x,
                (int)(position.lower_right_y * height_) + GetPosition().y
            }, start_.x, start_.y
        );
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
    for (auto enemy : enemies_)
        enemy.second->Draw(window);
}

Vector2i Map::GetNext(int i) {
    auto next = path_[i + 1];
    return {next.first, next.second};
}
