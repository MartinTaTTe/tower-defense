#pragma once

#include "state.hpp"
#include "../map/map.hpp"



class InputState : public State {
public:
    InputState(int width, int height);
    Event   CustomOnClick(Event event) override;
private:
    int     grid_width_;
    int     grid_height_;
};