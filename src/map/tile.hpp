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
    Tile(const Vector4f& body, TileType type = Grass);
    ~Tile() { };
    void     UpdateTexture();
    TileType type;
    bool     occupied;
};
