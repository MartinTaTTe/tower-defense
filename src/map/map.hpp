#pragma once
/*
Map is custom Canvas used for controlling all objects on the game map, such as Towers and Enemies.
*/
#include "tile.hpp"
#include "../gui/canvas.hpp"
#include "../enemies/enemy.hpp"

typedef std::vector<std::pair<Vector4f, Enemy*>> Enemies;
typedef std::vector<std::pair<int, int>> MapPath;

class Map : public Canvas {
public:
    Map(const Vector4i& body, const std::string& filePath);
    Map(const Vector4i& body, int width, int height);
    ~Map();
    void                UpdateTile(int x, int y, TileType& tileType, bool high);
    Tile*               GetTile(int x, int y) const;
    Event               CustomUpdate(int width, int height, double d_time);
    Vector2i            GetStart();
    Vector2i            GetEnd();
    Vector2i            GetGridSize();
    void                AddEnemy(const Vector4f& position, char type);
    void                CustomDraw(sf::RenderWindow& window) const override;
private:
    Vector2i            GetNext(int i);
    Enemies             enemies_;
    int                 grid_height_;
    int                 grid_width_;
    Vector2i            start_;
    Vector2i            end_;
    MapPath             path_;
    int                 path_length_;
};
