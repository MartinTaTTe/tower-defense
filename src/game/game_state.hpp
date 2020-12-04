#pragma once
/*
GameState is the actual game.
*/
#include "state.hpp"
#include "../map/map.hpp"

class GameState : public State {
public:
    GameState(int width, int height, const std::string& mapPath);
};
