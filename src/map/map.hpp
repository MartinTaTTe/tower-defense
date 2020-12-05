#pragma once
/*
Map is custom Canvas used for controlling all objects on the game map, such as Towers and Enemies.
*/
#include "tile.hpp"
#include "../gui/canvas.hpp"
#include "../enemies/enemy.hpp"

class Map : public Canvas {
public:
    Map(const Vector4i& body, const std::string& filePath);
    Map(const Vector4i& body, int width, int height);
    ~Map();
    void                UpdateTile(int x, int y, TileType& tileType);
    Tile*               GetTile(int x, int y) const;
    Event               CustomUpdate(int width, int height, double d_time);
private:
    std::vector<Enemy*> enemies_;
    int                 grid_height_;
    int                 grid_width_;
};
