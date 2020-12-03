#include "tile.hpp"
#include "../utils/app_constants.hpp"

Tile::Tile(TileType type)
    : Drawable(T_TILES[type]), type_(type) {

}

TileType Tile::GetType() const {
    return type_;
}
