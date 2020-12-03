#pragma once
/*
Base class.
A State manages everything that is currently happening, from graphics to logic.
*/
#include <SFML/Graphics.hpp>

class State {
public:
    State(const std::string& state_name);
    ~State();
    virtual State*      EventHandler(sf::RenderWindow& window, sf::Event& event) = 0;
    virtual void        Draw(sf::RenderWindow& window) = 0;
    const std::string&  GetName() const;
private:
    std::string         state_name_;
};
