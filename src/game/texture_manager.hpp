#pragma once

#include <SFML/Graphics.hpp>

typedef std::map<std::string, std::unique_ptr<sf::Texture>> TextureMap;
typedef TextureMap::iterator TMIterator;

sf::Texture&            GetTexture(const std::string& path);
static TMIterator       LoadTexture(const std::string& path);

static TextureMap       textures_;
