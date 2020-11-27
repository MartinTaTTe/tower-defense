#include "tile.hpp"

Tile::Tile(TileTypes type) : type_(type) {
    switch(type) {
        case Path:
            texturePath_ = "./textures/path.png";
            break;
        case Grass:
            texturePath_ = "./textures/grass.png";
            break;
        case Water:
            texturePath_ = "./textures/water.png";
            break;
        default:
            texturePath_ = "./textures/grass.png";
    }
    texture_ = GetTexture();
    texture_.setSmooth(true);
    sprite_ = sf::Sprite(texture_);
}

TileTypes Tile::GetType() const {return type_;}

sf::Texture& Tile::GetTexture() {
    return texture_manager.GetTexture(texturePath_);
}
sf::Sprite* Tile::GetSprite() {return &sprite_;}
void Tile::SetPos(float x, float y) {
    sprite_.setPosition(x,y);
}
void Tile::SetScale(float size) {
    sprite_.setScale(size / texture_.getSize().x, size / texture_.getSize().y);
}
void Tile::draw(sf::RenderWindow& window) const {
    window.draw(sprite_);
}
