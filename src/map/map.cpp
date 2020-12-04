#include "map.hpp"
#include <fstream>

Map::Map(const Vector4i& body, const std::string& filePath)
    : Canvas(body) {
    std::ifstream file(filePath);
    std::string line;
    std::getline(file,line);
    grid_width_  = stoi(line.substr(0, line.find('x')));
    grid_height_ = stoi(line.substr(line.find('x') + 1, line.find('x') + 2));
    float tile_width  = 1.0f / grid_width_;
    float tile_height = 1.0f / grid_height_;
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

}

Tile* Map::GetTile(int x, int y) const {
    if (x < grid_width_ && y < grid_height_)
        return dynamic_cast<Tile*>(drawables_[x + y * grid_width_].second);
    else return nullptr;
}
