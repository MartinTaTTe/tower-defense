#include "map.hpp"
#include <fstream>

Map::Map(const Vector4f& body, const std::string& filePath)
    : Canvas(sf::RectangleShape(sf::Vector2f())) {
    std::ifstream file(filePath);
    std::string line;
    std::getline(file,line);
    grid_width_  = stoi(line.substr(0, line.find('x')));
    grid_height_ = stoi(line.substr(line.find('x') + 1, line.find('x') + 2));
    float tile_width =  100.0f / grid_width_;
    float tile_height = 100.0f / grid_height_;
    int x = 0;
    int y = 0;
    while(std::getline(file,line)) {
        x = 0;
        for (auto i : line) {
            drawables_.push_back(std::pair<Vector4f, Drawable*>
                ({tile_width * x, tile_height * y, tile_width * (x + 1), tile_height * (y + 1)},
                 new Tile(static_cast<TileType>(i - '0'))));
            x++;
        }
        y++;
    }
    Update(body);
}

Map::Map(const Vector4f& body, int width, int height)
    : Canvas(sf::RectangleShape(sf::Vector2f())) {
    grid_width_  = width;
    grid_height_ = height;
    float tile_width =  100.0f / grid_width_;
    float tile_height = 100.0f / grid_height_;
    for(int y = 0; y < grid_height_; y++) {
        for (int x = 0; x < grid_width_; x++) {
            drawables_.push_back(std::pair<Vector4f, Drawable*>
                ({tile_width * x, tile_height * y, tile_width * (x + 1), tile_height * (y + 1)},
                 new Tile(static_cast<TileType>(1))));
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
