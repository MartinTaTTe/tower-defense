#pragma once

#include "state.hpp"
#include "../map/map.hpp"



class InputState : public State {
public:
    InputState();
    Event EventHandler(const sf::Event& sf_event) override;
    void  Draw(sf::RenderWindow& window) override;
private:
    std::string string_;
    sf::Text text_;
    std::string playerInput_;
    sf::Text playerText_;
    sf::Font font_;
    int width_;
    int height_;
    bool sizeGot_;
};