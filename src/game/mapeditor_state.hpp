#pragma once

#include "state.hpp"
#include "../map/map.hpp"

class MapEditorState : public State {
public:
    MapEditorState(const Vector2i& size, const int& width, const int& height, const std::string& name);
    Event             EventHandler(const sf::Event& event) override;
    void                Draw(sf::RenderWindow& window) override;
    void                Save();
private:
    Map*                map_;
    std::string         name_;
    int                 width_;
    int                 height_;
};