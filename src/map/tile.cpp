#include "tile.hpp"
#include "../utils/app_constants.hpp"

Tile::Tile(const Vector4f& body, TileType type)
    : Drawable(body, T_TILES[type]), type(type), occupied(false) {

}
