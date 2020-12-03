#pragma once
/*
The Texture Manager's purpose is to make sure no texture gets loaded more than once.
*/
#include <SFML/Graphics.hpp>

sf::Texture& GetTexture(const std::string& path);
