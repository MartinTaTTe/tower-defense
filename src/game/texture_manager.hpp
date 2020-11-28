#pragma once

#include <SFML/Graphics.hpp>

typedef std::map<std::string, std::unique_ptr<sf::Texture>> texture_map;

class TextureManager {
public:
    static TextureManager& GetManager();
    sf::Texture&        GetTexture(const std::string& path);
    texture_map::iterator LoadTexture(const std::string& path);

private:
    texture_map         textures_;
};

#define texture_manager TextureManager::GetManager()