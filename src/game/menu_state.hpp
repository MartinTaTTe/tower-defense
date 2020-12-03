#pragma once
/*
MenuState is the main menu, the first State a user sees.
*/
#include "state.hpp"

class MenuState : public State {
public:
    MenuState();
    Event EventHandler(const sf::Event& sf_event) override;
    void  Draw(sf::RenderWindow& window) override;
};
