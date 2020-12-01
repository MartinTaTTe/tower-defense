#include "tile.hpp"
#include "../utils/app_constants.hpp"

Tile::Tile(TileTypes type) : type_(type) {
    texture_ = GetTexture(T_TILES[type]);
    sprite_ = sf::Sprite(texture_);
}

TileTypes Tile::GetType() const { return type_; }

sf::Sprite* Tile::GetSprite() { return &sprite_; }

void Tile::SetPos(float x, float y) {
    sprite_.setPosition(x,y);
}

void Tile::SetScale(float size) {
    sprite_.setScale(size / texture_.getSize().x, size / texture_.getSize().y);
}

void Tile::Draw(sf::RenderWindow& window) const {
    window.draw(sprite_);
}
