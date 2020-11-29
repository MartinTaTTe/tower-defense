#include "texture_manager.hpp"

TextureManager& TextureManager::GetManager() {
    static TextureManager manager;
    return manager;
}

sf::Texture& TextureManager::GetTexture(const std::string& path) {
    auto texture = textures_.find(path);
    if(texture == textures_.end()) {
        texture = LoadTexture(path);
    }
    return *texture->second;
}

TextureMap::iterator TextureManager::LoadTexture(const std::string& path) {
    std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>(sf::Texture());
    texture->loadFromFile(path);
    return textures_.insert(std::make_pair(path, std::move(texture))).first;
}