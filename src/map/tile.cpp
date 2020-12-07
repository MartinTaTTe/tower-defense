#include "tile.hpp"
#include "../utils/app_constants.hpp"

Tile::Tile(const Vector4i& body, TileType type)
    : Drawable(body, T_TILES[type]), type_(type), occupied(false) {

}

TileType Tile::GetType() const {
    return type_;
}
