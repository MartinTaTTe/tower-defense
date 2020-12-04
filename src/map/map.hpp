#pragma once
/*
Map is custom Canvas used for controlling all objects on the game map, such as Towers and Enemies.
*/
#include "tile.hpp"
#include "../gui/canvas.hpp"

class Map : public Canvas {
public:
    Map(const Vector4f& body, const std::string& filePath);
    Map(const Vector4f& body, int width, int height);
    ~Map();
    Tile* GetTile(int x, int y) const;
private:
    int grid_height_;
    int grid_width_;
};
