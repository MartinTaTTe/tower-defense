#pragma once
/*
MenuState is the main menu, the first State a user sees.
*/
#include "state.hpp"

class MenuState : public State {
public:
    MenuState();
    State*              EventHandler(sf::RenderWindow& window, sf::Event& event) override;
    void                Draw(sf::RenderWindow& window) override;
};
