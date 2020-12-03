#pragma once
/*
GameState is the actual game.
*/
#include "state.hpp"
#include "../map/map.hpp"

class GameState : public State {
public:
    GameState(const Vector2i& size, const std::string& mapPath);
    State*              EventHandler(sf::RenderWindow& window, sf::Event& event) override;
    void                Draw(sf::RenderWindow& window) override;
private:
    Map*                map_;
};
