#pragma once

#include "state.hpp"
#include "../map/map.hpp"

class GameState : public State {
public:
    GameState(Map* map);
    State*              EventHandler(sf::RenderWindow& window, sf::Event& event) override;
    void                Draw(sf::RenderWindow& window) override;
private:
    Map*                map_;
};