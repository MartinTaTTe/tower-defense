#pragma once
#include <SFML/Graphics.hpp>
#include "../game/texture_manager.hpp"


enum TileTypes : int8_t {
    Path,
    Grass,
    Water
    
};

class Tile {
public: 
    Tile(TileTypes type = Grass);
    ~Tile() { };
    inline TileTypes    GetType() const;
    inline sf::Texture& GetTexture(); 
    void                SetPos(float x, float y);
    void                SetScale(float size);
    void                Draw(sf::RenderWindow& window) const;
    sf::Sprite*         GetSprite();
    
private:
    TileTypes           type_;
    std::string         texturePath_;
    sf::Texture         texture_;
    sf::Sprite          sprite_;
};
