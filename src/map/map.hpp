#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>

#include "tile.hpp"

typedef std::vector<std::vector<Tile*>> Grid;

class Map {
public:
    Map(int height = 8, int width = 8);
    Map(const std::string& filePath);
    ~Map();
    inline Tile*        GetTile(int x, int y) const;
    void                Draw(sf::RenderWindow& window);
private:
    int                 height_;
    int                 width_;
    Grid                tiles_; // tiles[height][width]
};