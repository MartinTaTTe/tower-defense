#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include "tile.hpp"

class Map {
public:
    Map(int height = 8, int width = 8);
    Map(const std::string filePath);
    ~Map();
    Tile*               GetTile(int x, int y) const;
    void                Draw(sf::RenderWindow& window);
private:
    int                 height_;
    int                 width_;
    std::vector<std::vector<Tile*>> tiles_; // tiles[height][width]
};