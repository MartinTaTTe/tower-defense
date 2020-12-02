#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "tile.hpp"
#include "../gui/canvas.hpp"

typedef std::vector<std::vector<Tile*>> Grid;

class Map : public Canvas {
public:
    Map(const Vector4f& body, const std::string& filePath);
    ~Map();
    Tile* GetTile(int x, int y) const;
private:
    int grid_height_;
    int grid_width_;
};