#pragma once
/*
GUIManager is used by each State and manages everything related to graphics and user interactions.
*/
#include <vector>

#include "canvas.hpp"

typedef std::pair<float, float> Proportion;

class GUIManager {
public:
    GUIManager();
    ~GUIManager();
    void AddCanvas(Proportion upper_left, Proportion lower_right);
    void AddCanvas(Proportion lower_right);

private:
    sf::RectangleShape body_;
    std::vector<Canvas*> canvases_;
};
