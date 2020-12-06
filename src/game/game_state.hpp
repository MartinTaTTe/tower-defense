#pragma once
/*
GameState is the actual game.
*/
#include "state.hpp"
#include "../map/map.hpp"
#include <vector>

typedef std::vector<std::vector<std::pair<int, char>>> Waves;

class GameState : public State {
public:
    GameState(int width, int height, const std::string& mapPath);
private:
    void        Update(double d_time) override;
    Event       CustomOnClick(Event event) override;
    void        ReadWaves(const std::string& filePath = W_BASIC_WAVES);
    void        SendWave();
    Waves       waves_;
    Vector2i    start_;
    double      since_last_spawn_;
    bool        paused_;
};
