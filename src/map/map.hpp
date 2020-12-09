#pragma once
/*
Map is custom Canvas used for controlling all objects on the game map, such as Towers and Enemies.
*/
#include "tile.hpp"
#include "../gui/canvas.hpp"
#include "../enemies/enemy.hpp"
#include "../towers/tower.hpp"

typedef std::vector<std::pair<Vector4f, Enemy*>> Enemies;
typedef std::vector<std::pair<int, int>> MapPath;

class Map : public Canvas {
public:
    Map(const Vector4f& body, const std::string& filePath);
    Map(const Vector4f& body, int grid_width, int grid_height);
    ~Map();
    Tile*               GetTile(int x, int y) const;
    Event               UpdateTile(Event event, TileType& tileType, bool highlight);
    Event               UpdateEnemies(double d_time);
    Event               UpdateTowers(double d_time, Event event);
    Vector2i            GetStart();
    Vector2i            GetEnd();
    Vector2i            GetGridSize();
    void                AddEnemy(const Vector2f& position, char type);
    void                CustomDraw(sf::RenderWindow& window) const override;
private:
    Vector2i            GetNextTile(int i);
    Enemies             enemies_;
    int                 grid_height_;
    int                 grid_width_;
    Vector2i            start_;
    Vector2i            end_;
    MapPath             path_;
    int                 path_length_;
    float               tile_width_;
    float               tile_height_;
    bool                death_occured_;
};
