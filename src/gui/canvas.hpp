#pragma once
/*
Canvases are used to manage Drawables and Buttons in a certain area.
*/
#include <vector>

#include "button.hpp"
#include "../utils/event.hpp"
#include "../utils/app_constants.hpp"

class Canvas;
typedef std::vector<std::pair<Vector4f, Canvas*>> Canvases;
typedef std::vector<std::pair<Vector4f, Button*>> Buttons;
typedef std::vector<std::pair<Vector4f, Drawable*>> Drawables;

class Canvas {
public:
    Canvas(const Vector4i& body);
    ~Canvas();
    Event               EventHandler(const Event& event);
    void                Update(const Vector4i& corners);
    void                Draw(sf::RenderWindow& window) const;
    void                AddButton(const Vector4f& position, const std::string& texturePath = T_DEFAULT_BUTTON, const Event& action = Event());
    void                AddDrawable(const Vector4f& position, const std::string& texturePath);
    void                AddCanvas(const Vector4f& position);
protected:
    Vector2i            GetPosition();
    Canvases            canvases_;
    Buttons             buttons_;
    Drawables           drawables_;
    int                 width_;
    int                 height_;
private:
    void                Update(int upper_left_x, int upper_left_y, int lower_right_x, int lower_right_y);
    sf::RectangleShape  body_;
};
