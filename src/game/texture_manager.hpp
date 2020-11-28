#pragma once

#include <SFML/Graphics.hpp>

class Texture_Manager {
public:
    static Texture_Manager& GetManager();
    sf::Texture& GetTexture(const std::string& path);
    std::map<const std::string, std::unique_ptr<sf::Texture>>::iterator LoadTexture(const std::string& path);

private:
    std::map<std::string, std::unique_ptr<sf::Texture>> textures_;
};

#define texture_manager Texture_Manager::GetManager()