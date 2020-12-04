#pragma once

#include "state.hpp"
#include "../map/map.hpp"



class InputState : public State {
public:
    InputState(int width, int height);
    Event EventHandler(const sf::Event& sf_event) override;
private:
    Event CustomMouseClick(Event event);
    std::string string_;
    sf::Text text_;
    std::string playerInput_;
    sf::Text playerText_;
    sf::Font font_;
    int grid_width_;
    int grid_height_;
};