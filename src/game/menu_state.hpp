#pragma once

#include "state.hpp"
#include "game_state.hpp"

class MenuState : public State {
public:
    MenuState();
    State*              EventHandler(sf::RenderWindow& window, sf::Event& event) override;
    void                Draw(sf::RenderWindow& window) override;
};