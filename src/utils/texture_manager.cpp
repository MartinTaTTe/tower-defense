#include "texture_manager.hpp"

typedef std::map<std::string, std::unique_ptr<sf::Texture>> TextureMap;
typedef TextureMap::iterator TMIterator;

static TextureMap textures_;

static TMIterator LoadTexture(const std::string& path) {
    std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>(sf::Texture());
    texture->loadFromFile(path);
    texture->setSmooth(true);
    return textures_.insert(std::make_pair(path, std::move(texture))).first;
}

sf::Texture& GetTexture(const std::string& path) {
    auto texture = textures_.find(path);
    if(texture == textures_.end()) {
        texture = LoadTexture(path);
    }
    return *texture->second;
}
