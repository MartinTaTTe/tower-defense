#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "button.hpp"

class Canvas {
public:
    Canvas(sf::RectangleShape body);
    ~Canvas();
    void EventHandler();
    void Draw(sf::RenderWindow& window);
private:
    sf::RectangleShape body_;
    std::vector<Button*> buttons_;
};
