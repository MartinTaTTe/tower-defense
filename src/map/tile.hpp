#pragma once
#include <../SFML/Graphics.hpp>


enum TileTypes {
    Path,
    Grass,
    Water,
    
};

class Tile {
public: 
    Tile(TileTypes type = Grass);
    TileTypes GetType() const;
    sf::Texture& GetTexture(); 
    void SetPos(float x, float y);
    void SetScale(float size);
    void draw(sf::RenderWindow& window) const;
    sf::Sprite* GetSprite();
    
private:
    TileTypes type_;
    std::string texturePath_;
    sf::Texture texture_;
    sf::Sprite sprite_;
};
