#pragma once

#include "state.hpp"
#include "../map/map.hpp"

class MapEditorState : public State {
public:
    MapEditorState(int width, int height, int grid_width, int grid_height);
    
    Event EventHandler(double d_time, const sf::Event& sf_event) override;
private:
    Event Save();
    Event CustomMouseClick(Event event);
    Event CustomMouseRelease(Event event);
    TileType selectedTile;
    int grid_width_;
    int grid_height_;

};