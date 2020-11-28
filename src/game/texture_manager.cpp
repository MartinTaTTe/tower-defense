#include "texture_manager.hpp"

Texture_Manager& Texture_Manager::GetManager() {
    static Texture_Manager manager;
    return manager;
}

sf::Texture& Texture_Manager::GetTexture(const std::string& path) {
    auto texture = textures_.find(path);
    if(texture == textures_.end()) {
        texture = LoadTexture(path);
    }
    return *texture->second;
}

std::map<const std::string, std::unique_ptr<sf::Texture>>::iterator Texture_Manager::LoadTexture(const std::string& path) {
    std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>(sf::Texture());
    texture->loadFromFile(path);
    return textures_.insert(std::make_pair(path, std::move(texture))).first;
}