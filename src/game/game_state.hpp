#pragma once
/*
GameState is the actual game.
*/
#include "state.hpp"
#include "../map/map.hpp"

class GameState : public State {
public:
    GameState(const std::string& mapPath);
    Event EventHandler(const sf::Event& sf_event) override;
    void  Draw(sf::RenderWindow& window) override;
private:
    Map*  map_;
};
