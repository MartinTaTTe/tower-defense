#pragma once

#include "state.hpp"
#include "../map/map.hpp"

class MapEditorState : public State {
public:
    MapEditorState(int width, int height, int grid_width, int grid_height);
    void        Update(double d_time) override;
    Event       CustomOnClick(Event event) override;
private:
    Event       Save();
    TileType    selectedTile;
    int         grid_width_;
    int         grid_height_;
};
