#pragma once
/*
GameState is the actual game.
*/
#include "state.hpp"
#include "../map/map.hpp"
#include <vector>

typedef std::vector<std::vector<std::pair<int, char>>> Waves;
typedef std::vector<char> Wave;

class GameState : public State {
public:
    GameState(int width, int height, const std::string& mapPath, const std::string& wavePath);
private:
    void        Update(double d_time) override;
    Event       CustomOnClick(Event event) override;
    void        ReadWaves(const std::string& filePath);
    void        AddWave();
    void        SendEnemy();
    std::string MakeDesc(int price, float damage, int range, bool ground, bool air);
    Waves       waves_;
    Wave        wave_;
    Vector2i    start_;
    double      since_last_spawn_;
    bool        paused_;
    int         player_lives_;
    float       player_gold_;
    char        selected_tower_;
    int         wave_count_;
    int         last_wave_;
};
