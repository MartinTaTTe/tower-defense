#pragma once
#include <SFML/Graphics.hpp>
#include "../gui/drawable.hpp"


enum TileType : int8_t {
    Path,
    Grass,
    Water 
};

class Tile : public Drawable {
public: 
    Tile(TileType type = Grass);
    ~Tile() { };
    TileType GetType() const;
    
private:
    TileType type_;
};
