#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "button.hpp"
#include "../utils/event.hpp"
#include "../utils/app_constants.hpp"

typedef std::vector<std::pair<Vector4f, Button*>> Buttons;
typedef std::vector<std::pair<Vector4f, Drawable*>> Drawables;

class Canvas {
public:
    Canvas(sf::RectangleShape body);
    ~Canvas();
    Event   EventHandler(const Event& event);
    void    Update(int upper_left_x, int upper_left_y, int lower_right_x, int lower_right_y);
    void    Update(const Vector2i& upper_left, const Vector2i& lower_right);
    void    Update(const Vector4i& corners);
    void    Draw(sf::RenderWindow& window);
    void    AddButton(const Vector4f& position, const std::string& texturePath = T_DEFAULT_BUTTON);
    void    AddDrawable(const Vector4f& position, const std::string& texturePath);
private:
    float               width_;
    float               height_;
    sf::RectangleShape  body_;
    Buttons             buttons_;
    Drawables           drawables_;
};
