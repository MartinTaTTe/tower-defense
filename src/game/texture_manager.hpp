#pragma once

#include <SFML/Graphics.hpp>

typedef std::map<std::string, std::unique_ptr<sf::Texture>> TextureMap;
typedef TextureMap::iterator TextureMapIterator;

class TextureManager {
public:
    static TextureManager& GetManager();
    sf::Texture&        GetTexture(const std::string& path);
    TextureMapIterator  LoadTexture(const std::string& path);

private:
    TextureMap          textures_;
};

#define texture_manager TextureManager::GetManager()