#pragma once
/*
Tiles are used as the base of a Map.
*/
#include "../gui/drawable.hpp"

enum TileType : int8_t {
    Path,
    Grass,
    Water 
};

class Tile : public Drawable {
public: 
    Tile(const Vector4i& body, TileType type = Grass);
    ~Tile() { };
    TileType GetType() const;
    bool     occupied;
private:
    TileType type_;
};
